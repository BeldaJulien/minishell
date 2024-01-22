#include "minishell.h"

void ft_create_pipes(int pipes[2])
{
    if (pipe(pipes) == -1) 
    {
        perror("Error creating pipe");
        exit(EXIT_FAILURE);
    }
}

void ft_create_pipes_array(int pipes[][2], int num_pipes) 
{
    int i;
    
    i = 0;
    while (i < num_pipes)
    {
        ft_create_pipes(pipes[i]);
        i++;
    }
}

void ft_close_pipes(int pipes[][2], int num_pipes) 
{
    int i;
    
    i = 0;
    while (i < num_pipes) 
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }
}

int ft_count_piped_commands(t_command *start_command) 
{
    int num_commands;
    t_command *current_command;
    
    num_commands = 1;
    current_command = start_command;

    while (current_command->next != NULL && current_command->next->tokenType == PIPE) 
    {
        num_commands++;
        current_command = current_command->next;
    }

    return num_commands;
}
