#include "minishell.h"

t_token_type ft_allocate_token_type(char *token) 
{
    if (ft_check_pipe(token)) {
        return PIPE;
    } else if (ft_check_heredoc(token)) {
        return HEREDOC;
    } else if (ft_check_lpr(token)) {
        return LPR;
    } else if (ft_check_rpr(token)) {
        return RPR;
    } else if (ft_check_and(token)) {
        return AND;
    } else if (ft_check_or(token)) {
        return OR;
    } else if (ft_check_append(token)) {
        return APPEND;
    } else if (ft_check_out(token)) {
        return OUT;
    } else if (ft_check_in(token)) {
        return IN;
    } else if (ft_check_not(token)) {
        return NOT;
    } else if (ft_check_end(token)) {
        return END;
    } else if (ft_check_command(token)) {
        return COMMAND_TYPE;
    } else if (ft_check_argument(token)) {
        return ARGUMENT_TYPE;
    } else if (ft_check_option(token)) {
        return OPTION_TYPE;
    } else {
        return UNKNOWN_TYPE;
    }
}

void custom_strtok(const char *input) {
    const char *start = input;
    const char *end;

    while (*start) {
        // Trouver le début d'un mot
        while (*start && (*start == ' ' || *start == '\t')) {
            putchar(*start);
            start++;
        }

        // Vérifier si le mot est entre guillemets
        if (*start == '"') {
            putchar(*start);  // Imprimer le guillemet ouvrant
            start++;

            // Trouver la fin du mot (jusqu'à la prochaine occurrence du guillemet fermant)
            end = strchr(start, '"');

            if (end == NULL) {
                end = start + strlen(start);
            }

            // Imprimer le mot
            print_word(start, end);

            if (*start == '"') {
                putchar(*start);  // Imprimer le guillemet fermant
                start++;
            }
        } else {
            // Trouver la fin du mot
            end = strchr(start, ' ');

            if (end == NULL) {
                end = start + strlen(start);
            }

            // Imprimer le mot
            print_word(start, end);
        }

        putchar('\n');
    }
}