#include "minishell.h"

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q my_minishell");
// }

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
void	shell(char *line)
{
	t_data	*data;
	int		status;

	data = get_data();
	data->tokens = tokenizer(line);
	if (data->tokens == NULL)
	{
		status = 258;
		return ;
	}
	expand_tokens(data->tokens);
	if (!check_syntax_error(data->tokens))
	{
		status = 258;
		free_token_list(&data->tokens);
		return ;
	}
	data->nodes = parser(data->tokens);
	if (!data->nodes)
	{
		free_token_list(&data->tokens);
		return ;
	}
	if (data->nodes->next)
		*is_pipe_heredoc() = 1;
	open_redir_file(data->nodes);
	status = execution(data);
	if (status >= 0)
		*get_status() = status;
	free_data(&data);
}

int	main(void)
{
	char	*line;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &signal_handler);
	initenv();
	while (1)
	{
		*is_pipe_heredoc() = 0;
		*is_run_heredoc() = 0;
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		shell(line);
		free(line);
	}
	exit(*get_status());
}
