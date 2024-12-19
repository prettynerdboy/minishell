#include "minishell.h"

int	check_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	run_parent_builtin(t_node *current_node)
{
	int	status;

	// パイプラインが1つのビルトインコマンドのみの場合
	if (current_node->command && current_node->command->args)
	{
		// ビルトインコマンドを親プロセスで実行
		status = execute_builtin(current_node->command);
		if (status != -1)
			return (status);
	}
	return (1);
}