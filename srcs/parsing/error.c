#include "minishell.h"

int	ft_check_if_its_any_white_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\r'
        || c == '\n' || c == '\v' || c == '\f')
        return (1);
    return (0);
}

t_Bool ft_check_if_only_spaces(const char *str) 
{
    if (str == NULL) 
        return FALSE;
    int i = 0;
    while (str[i] != '\0') 
    {
        if (str[i] != ' ') 
            return FALSE;
        i++;
    }
    return TRUE;
}

void ft_initialization_of_errors(t_mini *shell)
{
    if (shell != NULL) {
        shell->error = malloc(sizeof(t_error));
        if (shell->error != NULL) {
            shell->error->error = FALSE;
            shell->error->error_name = NULL;
            shell->error->next = NULL;
            shell->error->prev = NULL;
        }
    }
}

void ft_add_space_around_redirection(char *input) 
{
    char *src;
    char modifiedInput[2000];
    char *dest;

    src = input;
    dest = modifiedInput;
    while (*src != '\0') 
    {
        if ((*src == '>' || *src == '<') && *(src + 1) != *src) 
        {
            *dest++ = ' ';  // Ajouter un espace avant l'opérateur
            *dest++ = *src; // Copier l'opérateur
            *dest++ = ' ';  // Ajouter un espace après l'opérateur
        } else 
        {
            *dest++ = *src; // Copier le caractère actuel
        }
        src++;
    }

    *dest = '\0';  // Ajouter le caractère de fin de chaîne
    ft_strcpy(input, modifiedInput);
}