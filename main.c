#include "minishell.h"
#include <readline/history.h>
#include <stdio.h>

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
    nodes=parser(tokens);
    printf("=== Syntax Tree ===\n");
    print_tree(nodes, 0);
	open_redir_file(nodes);
    *status=execution(nodes);
	status = NULL;
}


// static void	signal_handler_test(int sig)
// {
//     // 改行と次のプロンプト表示
//     // printf("\n(SIGINT を検出しました) 次の操作を入力してください。\n");
// 	printf("\n");
//     // 必要なら手動でリフレッシュする
//     rl_on_new_line();  // 新しい行を作成
//     rl_replace_line("", 0);  // 現在の入力行をクリア
//     rl_redisplay();  // プロンプトを再表示
// }

int	main(void)
{
	int status;
	char *line;

	status = 0;
	// signal(SIGINT, signal_handler_test);
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		// 	break;
		shell(line, &status);
		free(line);
	}
	exit(status);
}