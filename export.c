#include "minishell.h"

static void print_env_var(char *env_var)
{
    char    *equal_sign;

    ft_putstr_fd("declare -x ", STDOUT_FILENO);
    equal_sign = ft_strchr(env_var, '=');
    if (equal_sign)
    {
        write(STDOUT_FILENO, env_var, equal_sign - env_var);
        ft_putstr_fd("=\"", STDOUT_FILENO);
        ft_putstr_fd(equal_sign + 1, STDOUT_FILENO);
        ft_putstr_fd("\"", STDOUT_FILENO);
    }
    else
        ft_putstr_fd(env_var, STDOUT_FILENO);
    ft_putstr_fd("\n", STDOUT_FILENO);
}

static void sort_env(char **env)
{
    int     i;
    int     j;
    char    *temp;

    i = 0;
    while (env[i + 1])
    {
        j = i + 1;
        while (env[j])
        {
            if (ft_strcmp(env[i], env[j]) > 0)
            {
                temp = env[i];
                env[i] = env[j];
                env[j] = temp;
            }
            j++;
        }
        i++;
    }
}

static void free_env_array(char **env)
{
    int i;

    if (!env)
        return ;
    i = 0;
    while (env[i])
    {
        free(env[i]);
        i++;
    }
    free(env);
}

static int print_sorted_env(void)
{
    extern char **environ;
    char    **env_copy;
    int     i;
    int     size;

    size = 0;
    while (environ[size])
        size++;
    env_copy = malloc(sizeof(char *) * (size + 1));
    if (!env_copy)
        return (1);
    i = 0;
    while (environ[i])
    {
        env_copy[i] = ft_strdup(environ[i]);
        i++;
    }
    env_copy[i] = NULL;
    sort_env(env_copy);
    i = 0;
    while (env_copy[i])
        print_env_var(env_copy[i++]);
    free_env_array(env_copy);
    return (0);
}

static int find_env_var(char *name)
{
    extern char **environ;
    int     i;
    size_t  name_len;

    i = 0;
    name_len = ft_strlen(name);
    while (environ[i])
    {
        if (ft_strncmp(environ[i], name, name_len) == 0
            && (environ[i][name_len] == '='
                || environ[i][name_len] == '\0'))
            return (i);
        i++;
    }
    return (-1);
}

static int copy_environ(char ***new_environ)
{
    extern char **environ;
    int     i;
    int     size;

    size = 0;
    while (environ[size])
        size++;
    *new_environ = malloc(sizeof(char *) * (size + 2));
    if (!*new_environ)
        return (1);
    i = 0;
    while (environ[i])
    {
        (*new_environ)[i] = ft_strdup(environ[i]);
        if (!(*new_environ)[i])
        {
            free_env_array(*new_environ);
            return (1);
        }
        i++;
    }
    (*new_environ)[i] = NULL;
    return (0);
}

static char *get_current_value(char *name)
{
    extern char **environ;
    int     index;
    char    *value;

    index = find_env_var(name);
    if (index == -1)
        return (NULL);
    value = ft_strchr(environ[index], '=');
    if (!value)
        return (ft_strdup(""));
    return (ft_strdup(value + 1));
}

static int handle_append(char *name, char *value, char ***new_environ, int index)
{
    char    *old_value;
    char    *temp;
    char    *new_var;

    old_value = get_current_value(name);
    if (old_value)
    {
        temp = ft_strjoin(old_value, value);
        free(old_value);
        if (!temp)
            return (1);
        new_var = ft_strjoin(name, "=");
        if (!new_var)
        {
            free(temp);
            return (1);
        }
        (*new_environ)[index] = ft_strjoin(new_var, temp);
        free(new_var);
        free(temp);
        if (!(*new_environ)[index])
            return (1);
    }
    else
    {
        new_var = ft_strjoin(name, "=");
        if (!new_var)
            return (1);
        (*new_environ)[index] = ft_strjoin(new_var, value);
        free(new_var);
        if (!(*new_environ)[index])
            return (1);
    }
    return (0);
}

static int update_env_var(char *arg)
{
    extern char **environ;
    char    **new_environ;
    int     index;
    char    *name;
    char    *value;

    if (copy_environ(&new_environ))
        return (1);
    if (ft_strnstr(arg, "+=", ft_strlen(arg)))
    {
        name = ft_substr(arg, 0, ft_strlen(arg) - ft_strlen(ft_strnstr(arg, "+=", ft_strlen(arg))));
        value = ft_strnstr(arg, "+=", ft_strlen(arg)) + 2;
        index = find_env_var(name);
        if (index == -1)
        {
            index = 0;
            while (new_environ[index])
                index++;
        }
        else
            free(new_environ[index]);
        if (handle_append(name, value, &new_environ, index))
        {
            free(name);
            free_env_array(new_environ);
            return (1);
        }
        free(name);
    }
    else
    {
        name = arg;
        if (ft_strchr(arg, '='))
        {
            name = ft_substr(arg, 0, ft_strlen(arg) - ft_strlen(ft_strchr(arg, '=')));
            index = find_env_var(name);
            free(name);
            if (index != -1)
            {
                free(new_environ[index]);
                new_environ[index] = ft_strdup(arg);
                if (!new_environ[index])
                {
                    free_env_array(new_environ);
                    return (1);
                }
            }
            else
            {
                index = 0;
                while (new_environ[index])
                    index++;
                new_environ[index] = ft_strdup(arg);
                if (!new_environ[index])
                {
                    free_env_array(new_environ);
                    return (1);
                }
                new_environ[index + 1] = NULL;
            }
        }
        else
        {
            if (find_env_var(arg) != -1)
            {
                free_env_array(new_environ);
                return (0);
            }
            index = 0;
            while (new_environ[index])
                index++;
            new_environ[index] = ft_strdup(arg);
            if (!new_environ[index])
            {
                free_env_array(new_environ);
                return (1);
            }
            new_environ[index + 1] = NULL;
        }
    }
    environ = new_environ;
    return (0);
}

static int is_valid_identifier(char *str)
{
    int i;

    if (!ft_isalpha(str[0]) && str[0] != '_')
        return (0);
    i = 1;
    while (str[i] && str[i] != '=' && !(str[i] == '+' && str[i + 1] == '='))
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

int ft_export(char **argv)
{
    int     i;

    if (!argv[1])
        return (print_sorted_env());
    i = 1;
    while (argv[i])
    {
        if (!is_valid_identifier(argv[i]))
        {
            ft_putstr_fd("export: not a valid identifier: ", 2);
            ft_putstr_fd(argv[i], 2);
            ft_putstr_fd("\n", 2);
            return (1);
        }
        if (update_env_var(argv[i]))
            return (1);
        i++;
    }
    return (0);
}