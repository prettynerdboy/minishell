/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:07:16 by hauchida          #+#    #+#             */
/*   Updated: 2024/12/20 05:45:28 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// リダイレクトなしの場合の実行関数
static int	execute_builtin_simple(char **argv)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		return (ft_echo(argv));
	else if (ft_strcmp(argv[0], "cd") == 0)
		return (ft_cd(argv));
	else if (ft_strcmp(argv[0], "pwd") == 0)
		return (ft_pwd(argv));
	else if (ft_strcmp(argv[0], "export") == 0)
		return (ft_export(argv));
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (ft_unset(argv));
	else if (ft_strcmp(argv[0], "env") == 0)
		return (ft_env(argv));
	else if (ft_strcmp(argv[0], "exit") == 0)
		return (ft_exit(argv));
	return (-1);
}

// リダイレクトありの場合の実行関数
static int	handle_builtin_redirect(t_node *cmd_node,
		int (*builtin_func)(char **))
{
	int		original_stdout;
	int		original_stdin;
	int		status;
	char	**argv;

	// 標準入出力をバックアップ
	original_stdout = dup(STDOUT_FILENO);
	original_stdin = dup(STDIN_FILENO);
	// リダイレクトの設定
	if (cmd_node->redirects && redirect(cmd_node->redirects) != 0)
	{
		close(original_stdout);
		close(original_stdin);
		ft_eprintf("%s: No such file or directory\n",
			cmd_node->redirects->filename->word);
		return (127);
	}
	// コマンドライン引数の準備
	argv = token_to_argv(cmd_node->args);
	if (!argv)
	{
		close(original_stdout);
		close(original_stdin);
		return (1);
	}
	// ビルトインコマンドの実行
	status = builtin_func(argv);
	// 標準入出力を元に戻す
	dup2(original_stdout, STDOUT_FILENO);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdout);
	close(original_stdin);
	wp_free(&argv);
	return (status);
}

// メインの実行関数
int	execute_builtin(t_node *cmd_node)
{
	char	**argv;
	int		status;

	if (!cmd_node || !cmd_node->args)
		return (-1);
	// リダイレクトの有無で処理を分岐
	if (cmd_node->redirects)
	{
		argv = token_to_argv(cmd_node->args);
		if (!argv)
			return (1);
		if (ft_strcmp(argv[0], "echo") == 0)
			status = handle_builtin_redirect(cmd_node, ft_echo);
		else if (ft_strcmp(argv[0], "cd") == 0)
			status = handle_builtin_redirect(cmd_node, ft_cd);
		else if (ft_strcmp(argv[0], "pwd") == 0)
			status = handle_builtin_redirect(cmd_node, ft_pwd);
		else if (ft_strcmp(argv[0], "export") == 0)
			status = handle_builtin_redirect(cmd_node, ft_export);
		else if (ft_strcmp(argv[0], "unset") == 0)
			status = handle_builtin_redirect(cmd_node, ft_unset);
		else if (ft_strcmp(argv[0], "env") == 0)
			status = handle_builtin_redirect(cmd_node, ft_env);
		else if (ft_strcmp(argv[0], "exit") == 0)
			status = handle_builtin_redirect(cmd_node, ft_exit);
		else
			status = -1;
		wp_free(&argv);
		return (status);
	}
	else
	{
		// リダイレクトがない場合は直接実行
		argv = token_to_argv(cmd_node->args);
		if (!argv)
			return (1);
		status = execute_builtin_simple(argv);
		wp_free(&argv);
		return (status);
	}
}
