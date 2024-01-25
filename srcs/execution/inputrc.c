#include "minishell.h"
/*
char *ft_create_inputrc_path() 
{
    char *home;
    char *inputrc_path;
    
    home = getenv("HOME");
    
    if (home == NULL) 
    {
        perror("Error getting HOME environment variable");
        exit(EXIT_FAILURE);
    }

    inputrc_path = ft_strjoin(home, "/.inputrc");
    
    if (inputrc_path == NULL) 
    {
        perror("Error with ft_strjoin in ft_create_inputrc_path");
        exit(EXIT_FAILURE);
    }

    return inputrc_path;
}

int ft_open_inputrc(const char *inputrc_path) 
{
    int fd;
    // solution to free inputrc_path
    char *non_const_inputrc_path;

    non_const_inputrc_path = strdup(inputrc_path);
    fd = open(inputrc_path, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
    
    if (fd == -1) 
    {
        perror("Error opening .inputrc file");
        free(non_const_inputrc_path);
        exit(EXIT_FAILURE);
    }

    return fd;
}
*/

/*
void ft_write_inputrc_content(int fd) 
{
    // Hide unwanted control characters like Ctrl+D, ^[[0;32m color, ^I for tab etc
    const char *content;
    ssize_t bytes_written;
    
    content = "set echo-control-characters Off\n";
     "set colored-stats On\n"
        "set prompt-color \\033[1;34m\n"
        "set visible-stats On\n"
        "set mark-directories On\n"
        "set time-stamp-string \"%Y-%m-%d %H:%M:%S%t\"\n"
        "set pre-echo-replace \"\\033[1;32m\"\n";

    bytes_written = write(fd, content, ft_strlen(content));
    
    if (bytes_written == -1) 
    {
        perror("Error writing to .inputrc file");
        close(fd);
        exit(EXIT_FAILURE);
    }
}

void ft_close_inputrc(int fd, char *inputrc_path) 
{
    close(fd);
    free(inputrc_path);
}

void ft_write_inputrc() 
{
    char *inputrc_path;
    int fd;

    inputrc_path = ft_create_inputrc_path();
    fd = ft_open_inputrc(inputrc_path);

    ft_write_inputrc_content(fd);

    ft_close_inputrc(fd, inputrc_path);
}
*/