#include "minishell.h"

void print_error(char *cmd, char *msg)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    if (cmd)
    {
        ft_putstr_fd(cmd, STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);
    }
    ft_putendl_fd(msg, STDERR_FILENO);
}

void error_exit(char *msg)
{	
    const char *red = "\033[31m"; 
    const char *reset = "\033[0m"; 
    write(2, red, 5);                
    ft_putendl_fd(msg, 2) ;      
    write(2, reset, 4);
    exit(EXIT_FAILURE);
}