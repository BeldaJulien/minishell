#include "minishell.h"

/*int ft_is_quote(char c) 
{
    if (c == '\'' || c == '"')
        return (1);
    return (0);
}

int ft_check_quotes_error(void)
{
    write (1, "Chaos, quote(s) problem", 24);
    return (1);
}

void ft_tokenize_with_quotes(char *input)
{
    char *current_char = input;
    char *starting_token = input;

    while (*current_char != '\0')
    {
        if (ft_is_quote(*current_char))
        {
            char quote = *current_char;
            current_char += 1;
            while (*current_char != quote && *current_char != '\0')
                current_char++;
        }
        else if (*current_char == '\0')
        {
            fprintf(stderr, "Error: Unterminated quote\n");
            return;
        }
        else if (*current_char == ' ')
        {
            *current_char = '\0';
            printf("Token : \"%s\"\n", starting_token);
            starting_token = ++current_char;
        }
        else 
            current_char++;
    }
    printf("Token : \"%s\"\n", starting_token);
}

void ft_follow_quotes_state(t_command *cmd) {
    int i = 0, j = 0;
    char *result = malloc(strlen(cmd->name) + 1);
    if (result == NULL) return;
    while (cmd->name[i] != '\0') {
        if (cmd->state == NORMAL) {
            if (cmd->name[i] == '\'')
                cmd->state = SINGLE_QUOTE;
            else if (cmd->name[i] == '\"')
                cmd->state = DOUBLE_QUOTE;
            else if (cmd->name[i] == '\\')
                cmd->state = ESCAPED;
            else
                result[j++] = cmd->name[i];
        } else if (cmd->state == SINGLE_QUOTE) {
            if (cmd->name[i] == '\'')
                cmd->state = NORMAL;
            else
                result[j++] = cmd->name[i];
        } else if (cmd->state == DOUBLE_QUOTE) {
            if (cmd->name[i] == '\"')
                cmd->state = NORMAL;
            else
                result[j++] = cmd->name[i];
        } else if (cmd->state == ESCAPED) {
            result[j++] = cmd->name[i];
            cmd->state = NORMAL;
        }
        i++;
    }
    result[j] = '\0';
    printf("Processed Command: %s\n", result);
    free(result);
}*/

// Fonction pour extraire un argument entre guillemets
char *ft_extract_quoted_argument(char *input) 
{
    char *start = strchr(input, '"');
    char *end = strchr(start + 1, '"');

    // Vérifier si les guillemets sont présents et sont correctement positionnés
    if (start != NULL && end != NULL && start < end) 
    {
        size_t arg_length = end - start - 1;
        char *argument = malloc(arg_length + 1);

        if (argument != NULL) 
        {
            strncpy(argument, start + 1, arg_length);
            argument[arg_length] = '\0';
            return argument;
        } 
        else 
        {
            perror("CHAOS, error allocating memory");
            exit(EXIT_FAILURE);
        }
    }

    return NULL; // Aucun argument trouvé entre guillemets
}

void ft_check_char_for_quote_type(char current_char, t_quote_type *quote_type) 
{
    if (*quote_type == NORMAL) 
    {
        if (current_char == '\'') 
        {
            *quote_type = SINGLE_QUOTE;
        } else if (current_char == '"') 
        {
            *quote_type = DOUBLE_QUOTE;
        }
    } else if (*quote_type == SINGLE_QUOTE) 
    {
        if (current_char == '\'') 
        {
            *quote_type = NORMAL;
        }
    } else if (*quote_type == DOUBLE_QUOTE) 
    {
        if (current_char == '"') 
        {
            *quote_type = NORMAL;
        } else if (current_char == '\\') {
            *quote_type = ESCAPED;
        }
    } else if (*quote_type == ESCAPED) {
        *quote_type = DOUBLE_QUOTE;
    }
    // Ici, vous pouvez traiter le caractère en fonction de son contexte
    // printf("Current char: %c, Quote type: %d\n", current_char, *quote_type);
}

t_quote_type ft_check_and_allocate_quote_type(char *token) 
{
    t_quote_type quote_type;
    int i;
    int tokenSize;
    char current_char;

    i = 0;
    tokenSize = ft_strlen(token);
    current_char = token[i];
    quote_type = NORMAL;

    while (i < tokenSize)
    {   
        ft_check_char_for_quote_type(current_char, &quote_type);
        i++;
    }
    return quote_type;
}
