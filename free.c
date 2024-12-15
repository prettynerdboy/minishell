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

void free_node(t_node **node)
{
    if (!node || !*node)
        return;
    free_token_list(&(*node)->args);
    if ((*node)->filename)
    {
        free((*node)->filename->word);
        free((*node)->filename);
        (*node)->filename = NULL;
    }
    if ((*node)->delimiter)
    {
        free((*node)->delimiter->word);
        free((*node)->delimiter);
        (*node)->delimiter = NULL;
    }
    free_node(&(*node)->redirects);
    free_node(&(*node)->command);
    free_node(&(*node)->next);
    free(*node);
    *node = NULL;
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

void free_data(t_data **data)
{
    if (!data || !*data)
        return;
    if ((*data)->tokens)
        free_token_list(&(*data)->tokens);
    if ((*data)->nodes)
        free_node(&(*data)->nodes);
    // free(*data);
    // *data = NULL;
}