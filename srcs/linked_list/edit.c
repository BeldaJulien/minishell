#include "minishell.h"

void ft_replace_in_list(t_env *new_node, t_env **envlist) 
{
    t_env *tmp = *envlist;
    while (tmp) 
    {
        if (strcmp(tmp->name, new_node->name) == 0) 
        {
            free(tmp->value);
            tmp->value = strdup(new_node->value);
            free(new_node->name);
            free(new_node->value);
            free(new_node);
            return;
        }
        tmp = tmp->next;
    }
}


// Go through list to apply callback function on each element
void ft_iterate_through_list_to_apply_function(t_commandList  *head, void (*callback)(void *data))
{
    t_command  *current = head->head;
    
    while (current != NULL)
    {
        callback(current->data);
    current = current->next;
    }
}

int ft_compareString(void *data, void *target)
{
    char *str = (char *)data;
    char *key = (char *)target;
    return ft_strcmp(str, key);
}
