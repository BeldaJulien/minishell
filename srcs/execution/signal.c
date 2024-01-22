#include "minishell.h"


void ft_receive_signal_from_user(int signal_num) 
{
    if (signal_num == SIGINT)
    {
        printf("\nSignal SIGINT (Ctrl+C) received. Stopping the current process.\n");
        ft_putstr_fd("\n", STDOUT_FILENO);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
        g_exit_code = 1;
        //exit(EXIT_SUCCESS);    
    }
    else if (signal_num == SIGQUIT)
    {
        rl_on_new_line();
        rl_redisplay();
    }
}

void ft_handle_signal_execution(int signal_num) 
{
    if (signal_num == SIGINT)
    {
        ft_putstr_fd("^C\n", STDOUT_FILENO);
        g_exit_code = 128 + SIGINT;
    }
    if (signal_num == SIGQUIT)
    {
        ft_putstr_fd("^\\Quit: ", STDOUT_FILENO);
        ft_putnbr_fd(SIGQUIT, STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
        g_exit_code = 128 + SIGQUIT;
    }
}

void ft_init_signals(void(*signals_handle)(int))
{
    struct sigaction	sig;
    
    sig = (struct sigaction){0};
    sigemptyset(&sig.sa_mask);
    sigaddset(&sig.sa_mask, SIGINT);
    sigaddset(&sig.sa_mask, SIGQUIT);
    sig.sa_handler = signals_handle;
    if (sigaction(SIGINT, &sig, NULL) != 0)
        perror("Error with SIGINT");
    if (sigaction(SIGQUIT, &sig, NULL) != 0)
        perror("Error with SIGQUIT");
}

void ft_init_terminal_settings(void)
{
    struct termios	termios;

    if ((tcgetattr(STDIN_FILENO, &termios)) == -1)
        exit(EXIT_FAILURE);
    termios.c_lflag &= ~(ECHOCTL);
    if ((tcsetattr(STDIN_FILENO, TCSANOW, &termios)) == -1)
        exit(EXIT_FAILURE);
}
