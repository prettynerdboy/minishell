#include "minishell.h"

static int create_sorted_env(char ***sorted_env)
{
    extern char **environ;
    int         env_count;
    int         i;

    env_count = 0;
    while (environ[env_count])
        env_count++;
    *sorted_env = malloc(sizeof(char *) * (env_count + 1));
    if (!*sorted_env)
        return (1);
    i = 0;
    while (environ[i])
    {
        (*sorted_env)[i] = ft_strdup(environ[i]);
        if (!(*sorted_env)[i])
        {
            wp_free(sorted_env);
            return (1);
        }
        i++;
    }
    (*sorted_env)[i] = NULL;
    return (0);
}

static void sort_env(char **sorted_env)
{
    int     i;
    int     j;
    char    *temp;

    i = 0;
    while (sorted_env[i + 1])
    {
        j = 0;
        while (sorted_env[j + 1])
        {
            if (ft_strcmp(sorted_env[j], sorted_env[j + 1]) > 0)
            {
                temp = sorted_env[j];
                sorted_env[j] = sorted_env[j + 1];
                sorted_env[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
}

static void print_env_var(char *env_var)
{
    char    *equal_sign;

    equal_sign = ft_strchr(env_var, '=');
    if (equal_sign)
    {
        *equal_sign = '\0';
        ft_putstr_fd("declare -x ", STDOUT_FILENO);
        ft_putstr_fd(env_var, STDOUT_FILENO);
        ft_putstr_fd("=\"", STDOUT_FILENO);
        ft_putstr_fd(equal_sign + 1, STDOUT_FILENO);
        ft_putstr_fd("\"\n", STDOUT_FILENO);
        *equal_sign = '=';
    }
    else
    {
        ft_putstr_fd("declare -x ", STDOUT_FILENO);
        ft_putstr_fd(env_var, STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
    }
}

static int validate_and_set_env(char *arg)
{
    char    *equal_sign;
    int     i;

    if (!ft_isalpha(arg[0]) && arg[0] != '_')
    {
        ft_putstr_fd("export: `", STDERR_FILENO);
        ft_putstr_fd(arg, STDERR_FILENO);
        ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
        return (1);
    }
    equal_sign = ft_strchr(arg, '=');
    if (equal_sign)
    {
        *equal_sign = '\0';
        if (setenv(arg, equal_sign + 1, 1) == -1)
        {
            *equal_sign = '=';
            return (1);
        }
        *equal_sign = '=';
    }
    else
        putenv(arg);  // 値なしの場合は単に変数名を登録
    return (0);
}

int ft_export(char **argv)
{
    char    **sorted_env;
    int     i;

    if (!argv[1])
    {
        if (create_sorted_env(&sorted_env))
            return (1);
        sort_env(sorted_env);
        i = 0;
        while (sorted_env[i])
            print_env_var(sorted_env[i++]);
        wp_free(&sorted_env);
        return (0);
    }
    i = 1;
    while (argv[i])
        if (validate_and_set_env(argv[i++]))
            return (1);
    return (0);
}
