#ifndef MINISHELL_H
# define MINISHELL_H

#include "../srcs/libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <termios.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdbool.h>

# define MAX_ARGUMENTS 100
# define MAX_PATH_LENGTH 4096
# define  MAX_INPUT_SIZE 1024
// File Descriptor
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define CD "cd"
# define ECHO "echo"
# define ENV "env"
# define EXIT "exit"
# define EXPORT "export"
# define PWD "pwd"
# define UNSET "unset"

typedef enum e_token_type
{
	PIPE,     // |
	HEREDOC,  // <<
	LPR,      // (
	RPR,      // )
	AND,      // &&
	OR,       // ||
	APPEND,   // >>
	OUT,      // >
	IN,       // <
	NOT,      // string
	END,      // end of cmd
    COMMAND_TYPE,
    ARGUMENT_TYPE,
    OPTION_TYPE,
    UNKNOWN_TYPE  
} t_token_type;

typedef enum e_quote 
{
    NORMAL,        // no quote
    SINGLE_QUOTE,
    DOUBLE_QUOTE,
    ESCAPED        // backslash
} t_quote_type;
typedef enum Bool
{
	FALSE,
	TRUE
} t_Bool;
typedef enum node_type {
    ENV_NODE,
    COMMAND_NODE
} t_node_type;
typedef struct s_command
{
    char *name;
    void *data;
    char **args;
    int argCount;
    char    *redirectFile;
    int fd[2];
    // int fdread;
    // int fdwrite;
    struct s_command *next;
    struct s_command *prev;
    t_token_type tokenType;
    t_quote_type quoteType;
} t_command;

typedef struct s_commandList
{
    int length;
    struct s_command *head;
    struct s_command *tail;
}   t_commandList;

typedef struct s_error
{
    t_Bool error;
    char *error_name;
    struct s_error *next;
    struct s_error *prev;
} t_error;

typedef struct s_env
{
    char *name;
    char *value;
    char **g_env;
    struct s_env *next;
    struct s_env *prev;
} t_env;

typedef struct t_envList
{
    int length;
    struct s_env *head;
    struct s_env *tail;
}
    t_envList;

typedef struct s_redir
{
    char *file_name;
    int redirection_type;
    struct s_redir *next;
    struct s_redir *prev;
} t_redir;

typedef struct s_execute
{
    int *fd;
    int pfd[2];
    int *pid;
    int *status;
    int active;
    struct s_execute *next;
} t_execute;

typedef struct s_global
{
    t_commandList *arguments;
    t_commandList *commands;
    t_command *cmd;
    t_env *envlist;
    t_redir *redirections;
    t_error *error;
    t_execute *execute;
} t_global;

typedef struct s_mini
{
    char *av;
    int numberOfCommands;
    int fd_history;
    int status;
    int stdin_fd;
    int stdout_fd;
    t_commandList *commands;
    t_global *child; // TO DO : comment rappeler t_global etant plus bas ?
    t_global *exec;  // est-ce quil faut plutot rappeler la structure NON t_global ?
    t_error *error;
} t_mini;

// BUILT-IN
// cd
int	    cd(t_command *command);
// echo
int     echo(t_command *cmd);
// env
int 	env(t_env *env_list);
void    ft_display_envList(t_env *envList);
// exit
int     ft_search_exit_arg_in_envList(t_command *command, t_env *envList);
int     ft_check_exit_arg_value(char *value);
int	    ft_exit(t_command *command, t_env *envList);
// export_util
void    ft_split_string_export_argument(const char *arg, char **name, char **value);
int     ft_check_reserved_env_variables(const char *var_name);
// export
int     ft_is_alpha(char c);
int     ft_check_variable_definition(char *arg);
int     ft_check_export_args(t_command *command);
void    ft_print_exported_vars(t_env *envList);
int     ft_export(t_env **envlist, t_command *cmd);
// pwd
int 	pwd(void);
// unset
int	    ft_unset(t_env **env_list, t_command *cmd);

// EXECUTION
// builtins
int	    ft_is_builtin(t_command *cmd);
int	    ft_execute_builtin(t_command *cmd, t_env *envList);
// command
void	ft_execute_command(t_command *command, t_env *envList);
void    ft_execute_external_command(t_command *command, t_commandList *commandList, char **envp);
// destroy
void    ft_destroy_command(t_commandList *commandList);
void	ft_destroy_current_shell(t_mini *mini);
// path
char    *ft_lookfor_command_and_build_path(char *path, t_commandList *commandList);
void    ft_execute_command_with_path(t_command *command);
void    ft_execute_command_with_relative_path(t_command *command);
void    ft_execute_command_with_absolute_path(t_command *command);
// tool_exec
char    *ft_strjoin_free(char const *s1, char const *s2, int free_s1);
t_env   *create_node2(char *var, char *value);
t_env   *ft_copy_env_list(t_env *src);
void    free_split(char **arr);

// LINKED LIST
// add
void        ft_add_to_list(t_env **envlist, t_env *new_node);
int	        ft_add_envVar_to_list(t_env **envlist, t_env *new_node, t_command *command);
void        ft_append_to_list(t_commandList *commandList, t_command *newCommand);
void        ft_append_to_list_arg(t_command *command, char *arg);
void        ft_print_command(void *data);
void        ft_print_list(t_commandList *head, void (*printFunction)(void *data));

// clean
void        ft_free_list(t_commandList  *head);
void	    ft_free_array(char **array);
void        ft_delete_list(t_env *envlist);
void        ft_free_node(t_command  *node);
void        ft_free_env_node(t_env *new_node, t_env *tmp, char *str);
void        ft_delete_node(t_commandList **head, t_command *node);
void        ft_free_envList(t_env *envList);
// create
t_env	    *ft_create_node_for_args(char *var_array);
t_command   *ft_create_node_for_command(void);
t_env       *ft_create_node_for_export_argument(char *name, char *value);
t_env	    *ft_create_node_for_envVar(t_command *command);
void        *ft_create_node_by_type(void *node, t_node_type type, t_command *command);
// duplicate
t_env	    *ft_envlist_duplicate(t_env **envlist);
t_env	    *ft_duplicate_node(char *name, char *value);
char        **ft_env_duplicate(char **envp);
// edit
void	    ft_replace_in_list(t_env *new_node, t_env **envlist);
void        ft_iterate_through_list_to_apply_function(t_commandList  *head, void (*callback)(void *data));
int         ft_compareString(void *data, void *target);
// list
int         ft_is_empty_list(t_commandList    *head);
int	        ft_is_in_list(char	*var, t_env **envlist);
int         ft_get_commandList_size(t_commandList  *head);
int	        ft_get_envList_size(t_env **list);
t_env	    *ft_get_in_list(char *var, t_env **envlist);
void        ft_print_generic(void *data);
// node
t_command   *ft_get_previous_node(t_commandList  *head, t_command  *node);
t_command   *ft_find_node(t_commandList  *head, void *target);
void	    ft_swap_nodes(t_env *tmp);
void        *ft_get_last_element_in_list(t_commandList *head);
t_env       *ft_find_envVar(t_envList *envList, const char *targetName);

// MINISHELL
void	    ft_exit_shell(t_mini *shell);
void        ft_initialize_commandList(t_commandList *commandList);
t_env       *ft_initialize_environment(char **env);
void	    ft_initialize_minishell(t_mini *shell);
t_env       *ft_initialize_all(t_mini *shell, char **envp, t_env *envList);
// history & prompt
void	    ft_custom_prompt_msg(t_mini *shell);
void        ft_manage_history(t_mini *shell, const char *input);
void        ft_rl_replace_line(const char *str, int i);
// functions about signals
void        ft_receive_signal_from_user(int signal_num);
void        ft_handle_signal_execution(int signal_num);
void        ft_init_signals(void(*signals_handle)(int));
void        ft_init_terminal_settings(void);

// PARSING
// error
void            ft_initialization_of_errors(t_mini *shell);
// expansion
int             ft_is_valid_env_char(char c);
char            *ft_getenv_var_value(const char *name);
int             ft_calculate_new_length(const char *cmd, int last_exit_status);
char            *ft_expand_env_variables(t_command *command, int last_exit_status);
// parser
void            ft_init_new_node(t_commandList *commandList, t_command *command, char *token, int tokenIndex);
void            ft_createNode_initNode_appendNodeToList(t_commandList *commandList, char *token, int tokenIndex);
void            ft_process_argument(t_commandList *commandList, t_command *command, char *token, int argIndex);
void            ft_process_cd_argument(t_command *command, char *arg);
int             ft_split_arg(t_commandList *commandList, char *input);
int             ft_launch_parsing(t_commandList *commandList, char *input ,t_env *envList, char **envp);
// pipe
int             ft_is_pipe_or_redir(char c);
void            ft_parse_pipes(t_command *commands, char *input);
// quote
int			    ft_is_quote(char c);
int			    ft_check_quotes_error(void);
void            ft_follow_quotes_state(t_command *cmd);
char            *ft_extract_quoted_argument(char *input);
void		    ft_tokenize_with_quotes(char *input);
// char         *ft_strtrim_with_quotes(char *str); where are you ?
// char         *ft_strtok_quoted(char *str, const char *delim); where are you ? 
// redirection
void            ft_redirect_stdout(t_command *command, char *input);
void            ft_redirect_stdin(t_command *command, char *input);
// tool_parse
int	            ft_is_white_space(char c);
t_Bool          ft_check_only_spaces(const char *str);
// type
t_token_type    ft_check_and_allocate_token_type(char *token, int tokenIndex);
void            ft_check_char_for_quote_type(char current_char, t_quote_type *quote_type);
t_quote_type    ft_check_and_allocate_quote_type(char *token);
// util
char            *ft_strcpy(char *dest, const char *src);
char            *ft_strpbrk(const char *s1, const char *s2);
char            *ft_custom_strdup(const char *str);
char            *ft_strndup(const char *s, size_t n);

// GLOBAL
extern int	g_exit_code;
void        rl_replace_line(const char *str, int i);

// MAIN
int         main(int ac, char **av, char **envp);
void        ft_write_inputrc(void);
void	    ft_exit_shell(t_mini *shell);

#endif