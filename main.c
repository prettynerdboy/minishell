#include "minishell.h"
#include <readline/history.h>
#include <stdio.h>

__attribute__((destructor)) static void destructor()
{
	system("leaks -q a.out");
}

// ノード種別を文字列に変換する関数
// *第１引数 kind - ?
const char	*node_kind_to_string(t_node_kind kind)
{
	switch (kind)
	{
	case ND_PIPELINE:
		return ("PIPELINE");
	case ND_SIMPLE_CMD:
		return ("SIMPLE_CMD");
	case ND_REDIR_OUT:
		return ("REDIR_OUT");
	case ND_REDIR_IN:
		return ("REDIR_IN");
	case ND_REDIR_APPEND:
		return ("REDIR_APPEND");
	case ND_REDIR_HEREDOC:
		return ("REDIR_HEREDOC");
	default:
		return ("UNKNOWN");
	}
}

// トークンリストを出力する関数
// *第１引数 tok - ?
void	print_tokens(t_token *tok)
{
	while (tok)
	{
		printf("  [WORD: %s, TYPE: %d]\n", tok->word, tok->type);
		tok = tok->next;
	}
}

// 再帰的に木構造を出力する関数
// *第１引数 node - ?
// *第２引数 depth - ?
void	print_tree(t_node *node, int depth)
{
	if (!node)
		return ;
	// インデントを出力
	for (int i = 0; i < depth; i++)
		printf("  ");
	// ノードの情報を出力
	printf("Node: %s\n", node_kind_to_string(node->kind));
	if (node->kind == ND_SIMPLE_CMD)
	{
		printf("  Args:\n");
		print_tokens(node->args);
		printf("  Redirects:\n");
		print_tree(node->redirects, depth + 1);
	}
	else if (node->kind == ND_REDIR_OUT || node->kind == ND_REDIR_IN)
	{
		printf("  Filename: %s\n", node->filename->word);
	}
	// 子ノード（パイプラインや次のノード）を出力
	if (node->command)
	{
		printf("  Command:\n");
		print_tree(node->command, depth + 1);
	}
	if (node->next)
	{
		printf("  Next Node:\n");
		print_tree(node->next, depth);
	}
}

// shell起動関数
// *第１引数 line - 入力されたコマンドライン文字列
// *第２引数 status - ?
void	shell(char *line, int *status)
{
	t_token	*tokens;
	t_node	*nodes;

	tokens = tokenizer(line);
	if (tokens == NULL)
	{
		*status = 258; // bashの構文エラー時の終了ステータス
		return ;
	}
	if (!check_syntax_error(tokens))
	{
		*status = 258;
		free_token_list(&tokens);
		return ;
	}
	nodes = parser(tokens);
	printf("=== Syntax Tree ===\n");
	print_tree(nodes, 0);
	open_redir_file(nodes);
	*status = execution(nodes);
	free_token_list(&tokens);
	free_node(nodes);
	// printf("===================\n");
	// *status = execution(nodes);
	// status = NULL;
}

void	reset_prompt(void)
{
	printf("\n");
	rl_on_new_line();       // 新しい行を作成
	rl_replace_line("", 0); // 現在の入力行をクリア
	rl_redisplay();         // プロンプトを再表示
}

static void	signal_handler(int sig, siginfo_t *info, void *context)
{
	if (info->si_pid == 0)
		return ;
	if (sig == SIGINT)
		reset_prompt();
}

int	main(void)
{
	int status;
	int *loading;
	char *line;

	status = 0;

	struct sigaction sigaction_t;

	sigaction_t.sa_flags = SA_SIGINFO;
	sigaction_t.sa_sigaction = &signal_handler;
	sigemptyset(&sigaction_t.sa_mask);
	signal(SIGQUIT, SIG_IGN);
	if (sigaction(SIGINT, &sigaction_t, NULL) < 0)
	{
		perror("sigaction fatal error");
	}

	// signal(SIGINT, signal_handler_test);
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		shell(line, &status);
		free(line);
		break ;
	}
	exit(status);
}