#include "minishell.h"

void ft_redirect_stdout(t_command *command, char *input) 
{
    int i = 0;
    while (input[i] != '\0') 
    {
        if (input[i] == '>') 
        {
            if (input[i + 1] == '>') 
            {
                command->tokenType = APPEND; 
                i += 2;
            } 
            else 
            {
                command->tokenType = OUT; 
                i += 1;
            }
            while (input[i] == ' ') i++; 
            int startIndex = i;
            while (input[i] != ' ' && input[i] != '\0') i++;
            int fileLength = i - startIndex;
            command->redirectFile = (char *)malloc(fileLength + 1);
            if (command->redirectFile == NULL)
                return;
            ft_strlcpy(command->redirectFile, input + startIndex, fileLength + 1);

            // Supposons que vous ayez un champ pour stocker le fichier de redirection
            break; // Supposer qu'une seule redirection est traitée par ligne de commande
        }
        i++;
    }
}

void ft_redirect_stdin(t_command *command, char *input) {
    int i = 0;
    while (input[i] != '\0') {
        if (input[i] == '<') {
            if (input[i + 1] == '<') {
                command->tokenType = HEREDOC; 
                i += 2;
            } else {
                command->tokenType = IN; 
                i += 1;
            }
            while (input[i] == ' ') i++; 
            int startIndex = i;
            while (input[i] != ' ' && input[i] != '\0') i++;
            int fileLength = i - startIndex;
            command->redirectFile = (char *)malloc(fileLength + 1);
            if (command->redirectFile == NULL)
                return;
            ft_strlcpy(command->redirectFile, input + startIndex, fileLength + 1);

            // Supposons que vous ayez un champ pour stocker le fichier de redirection
            break; // Supposer qu'une seule redirection est traitée par ligne de commande
        }
        i++;
    }
}
