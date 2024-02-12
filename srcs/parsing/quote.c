#include "minishell.h"

int process_single_quoted_argument(t_commandList *commandList, t_command *command, char *token, int argIndex) 
{
    char *single_quoted_argument = extract_single_quoted_argument(token);
    if (single_quoted_argument != NULL) 
    {
        // Traitez l'argument entre des quotes simples
        printf("Processing single-quoted argument %d: %s\n", argIndex, single_quoted_argument);
        process_argument(commandList, command, single_quoted_argument, argIndex);
        free(single_quoted_argument);

        return 1; // Indique que l'argument a été traité
    }

    return 0; // Indique que l'argument n'a pas été traité
}

char *extract_single_quoted_argument(char *input) {
    // Vérifier si le premier caractère est une quote simple
    if (input[0] == '\'' && input[strlen(input) - 1] == '\'') {
        // Allouer de la mémoire pour l'argument extrait
        char *argument = (char *)malloc(strlen(input));

        // Copier le contenu de l'argument entre les quotes
        size_t i, j;
        for (i = 1, j = 0; i < strlen(input) - 1; i++) {
            argument[j++] = input[i];
        }

        // Ajouter un caractère de fin de chaîne
        argument[j] = '\0';

        return argument;
    }

    return NULL; // Pas entre des quotes simples
}

int process_double_quoted_argument(t_commandList *commandList, t_command *command, char *token, int argIndex) {
    char *double_quoted_argument = extract_double_quoted_argument(token);
    if (double_quoted_argument != NULL) {
        // Traitez l'argument entre des quotes doubles
        printf("Processing double-quoted argument %d: %s\n", argIndex, double_quoted_argument);
        process_argument(commandList, command, double_quoted_argument, argIndex);
        free(double_quoted_argument);

        return 1; // Indique que l'argument a été traité
    }

    return 0; // Indique que l'argument n'a pas été traité
}

char *extract_double_quoted_argument(char *input) 
{
    // Vérifier si le premier caractère est une quote double
    if (input[0] == '\"' && input[strlen(input) - 1] == '\"') {
        // Allouer de la mémoire pour l'argument extrait
        char *argument = (char *)malloc(strlen(input));

        // Copier le contenu de l'argument entre les quotes
        size_t i, j;
        for (i = 1, j = 0; i < strlen(input) - 1; i++) {
            argument[j++] = input[i];
        }

        // Ajouter un caractère de fin de chaîne
        argument[j] = '\0';

        return argument;
    }

    return NULL; // Pas entre des quotes doubles
}

int process_quoted_argument(t_commandList *commandList, t_command *command, char *token, int argIndex) 
{
    char quote_char = '\0';

    // Vérifier si le premier caractère est une quote simple ou double
    if (token[0] == '\'' || token[0] == '\"') 
    {
        quote_char = token[0];
    } else 
    {
        return 0;  // Pas de quote, renvoyer 0
    }

    // Allouer de la mémoire pour l'argument extrait
    char *argument = (char *)malloc(strlen(token));
    if (argument == NULL) 
    {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    // Copier le contenu de l'argument entre les quotes (en évitant les méta-caractères)
    size_t i, j;
    for (i = 1, j = 0; i < strlen(token); i++) 
    {
        if (token[i] == quote_char && token[i + 1] == '\0') {
            break;  // Fin de l'argument
        } else {
            argument[j++] = token[i];
        }
    }

    // Ajouter un caractère de fin de chaîne
    argument[j] = '\0';

    // Traiter l'argument en fonction du type de quote
    if (quote_char == '\'') {
        printf("Processing single-quoted argument %d: %s\n", argIndex, argument);
        process_argument(commandList, command, argument, argIndex);
    } else if (quote_char == '\"') {
        printf("Processing double-quoted argument %d: %s\n", argIndex, argument);
        process_argument(commandList, command, argument, argIndex);
    }

    free(argument);
    return 1; // Indiquer que l'argument entre quotes a été traité
}




