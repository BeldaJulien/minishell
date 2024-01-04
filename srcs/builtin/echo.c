#include "minishell.h"

int echo(t_command *cmd) 
{
    const char *message;
    int i;
    int suppressNewline;
    
    message = "An error occurred: not enough arguments\n";
    i = 1;
    suppressNewline = 0;
    if (cmd == NULL || cmd->args == NULL) 
    {
        write(STDERR_FILENO, message, strlen(message));
        return 1;
    }
    if (cmd->args[1] != NULL && strcmp(cmd->args[1], "-n") == 0) 
    {
        suppressNewline = 1;
        i++;
    }
    while (cmd->args[i] != NULL) 
    {
        write(STDOUT_FILENO, cmd->args[i], strlen(cmd->args[i]));
        if (cmd->args[i + 1] != NULL)
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if (!suppressNewline) 
        write(STDOUT_FILENO, "\n", 1);
    return 0;
}
