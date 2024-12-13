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
    
    // コマンドの引数を解放
    free_token_list(&node->args);
    
    // リダイレクトのファイル名とデリミタを解放
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
    
    // 再帰的に子ノードを解放
    free_node(node->redirects);
    free_node(node->command);
    free_node(node->next);
    
    // ノード自体を解放
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