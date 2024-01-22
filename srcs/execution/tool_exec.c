#include "minishell.h"

void free_split(char **arr)
{
    if (arr == NULL)
        return;

    int i = 0;
    while (arr[i] != NULL) {
        free(arr[i]);
        i++;
    }

    free(arr);
}

t_env *ft_copy_env_list(t_env *src)
{
    t_env *new_list = NULL;
    t_env *last = NULL;

    while (src != NULL)
    {
        t_env *new_node = create_node2(src->name, src->value);
        if (new_node != NULL)
        {
            if (last == NULL)
                new_list = new_node;
            else
                last->next = new_node;

            last = new_node;
        }
        src = src->next;
    }

    return new_list;
}

// Modifier la fonction create_node2 dans tool_exec.c
t_env *create_node2(char *var, char *value)
{
    t_env *new_node;
    new_node = malloc(sizeof(t_env));

    if (new_node)
    {
        new_node->name = ft_strdup(var);
        new_node->value = ft_strdup(value); // Assurez-vous que value est une chaîne de caractères
        new_node->next = NULL;
        return new_node;
    }
    return NULL;
}

char *ft_strjoin_free(char const *s1, char const *s2, int free_s1)
{
    if (s1 == NULL || s2 == NULL)
        return NULL;

    size_t len_s1 = strlen(s1);
    size_t len_s2 = strlen(s2);

    char *result = malloc(len_s1 + len_s2 + 1);
    if (result == NULL)
        return NULL;

    strcpy(result, s1);
    strcat(result + len_s1, s2);

    if (free_s1)
        free((void *)s1);

    return result;
}
