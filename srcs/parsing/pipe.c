#include "minishell.h"

void ft_parse_pipes(t_command *commands, char *input) 
{
    int i = 0;
    int cmdIndex = 0;
    int startIndex = 0;
    while (input[i] != '\0') {
        if (input[i] == '|') {
            if (input[i + 1] == '|') {
                commands[cmdIndex].tokenType = OR;
                i += 2;
            } else {
                commands[cmdIndex].tokenType = PIPE;
                i += 1;
            }

            int nameLength = i - startIndex - 1; // -1 pour ne pas inclure le pipe dans le nom
            commands[cmdIndex].name = (char *)malloc(nameLength + 1);
            if (commands[cmdIndex].name == NULL)
                return;
            ft_strlcpy(commands[cmdIndex].name, input + startIndex, nameLength + 1);
            cmdIndex++;
            startIndex = i;
        }
        i++;
    }
    // Capture last command after the last pipe or if there are no pipes
    if (startIndex < i) {
        int nameLength = i - startIndex;
        commands[cmdIndex].name = (char *)malloc(nameLength + 1);
        if (commands[cmdIndex].name == NULL)
            return;
        ft_strlcpy(commands[cmdIndex].name, input + startIndex, nameLength + 1);
    }
}
