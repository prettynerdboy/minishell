#include "minishell.h"

void free_token_list(t_token **head)
{
    t_token *current;
    t_token *next;

    if (!head || !*head) 
        return;
    current = *head;
    while (current)
    {
        next = current->next;
        free(current->word);
        free(current);
        current = next;
    }

    *head = NULL; 
}

void free_node(t_node *node)
{
    if (!node)
        return;
    free_token_list(&node->args);
    if (node->filename)
    {
        free(node->filename->word);
        free(node->filename);
    }
    if (node->delimiter)
    {
        free(node->delimiter->word);
        free(node->delimiter);
    }
    free_node(node->redirects);
    free_node(node->command);
    free_node(node->next);
    free(node);
} 

void wp_free(char ***str)
{
    int i;

    if (!str || !*str)
        return;
    i = 0;
    while ((*str)[i])
    {
        free((*str)[i]);
        (*str)[i] = NULL;
        i++;
    }
    free(*str);
    *str = NULL;
}