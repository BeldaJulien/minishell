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
// # define ECHO "echo"
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

typedef t_token_type (*TokenChecker)(char *);

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
    char *redirectFile;
    int fd[2]; // Pour la gestion des tubes
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
    // char **g_env;
    struct s_env *next;
    struct s_env *prev;
} t_env;

typedef struct s_redir
{
    char *file_name;
    int redirection_type;
    struct s_redir *next;
    struct s_redir *prev;
} t_redir;

typedef struct s_execute
{
    int pfd[2]; // Descripteurs de fichier pour les tubes globaux
    int *pid;
    int *status;
    int active;
    struct s_execute *next;
} t_execute;

typedef struct s_mini
{
    char *av;
    // int numberOfCommands;
    // int status;
    int fd_history;
    int stdin_fd;
    int stdout_fd;
    t_commandList *commands;
    t_error *error;
} t_mini;

// BUILT-IN

// cd
int	            cd(t_command *command);
void            ft_process_cd_argument(t_command *command, char *arg);

// echo
void            ft_handle_argument(char *arg);
void            ft_handle_space();
void            ft_echo_args(char **args, int g_exit_code);
void            print_error_message(char *message);
int             echo(char **args, int g_exit_code);
// env
int 	        env(t_env *env_list);
void            ft_display_envList(t_env *envList);
// exit
int             ft_search_exit_arg_in_envList(t_command *command, t_env *envList);
int             ft_check_exit_arg_value(char *value);
int	            ft_exit(t_command *command, t_env *envList);
// export_util
void            ft_split_string_export_argument(const char *arg, char **name, char **value);
int             ft_check_reserved_env_variables(const char *var_name);
// export
int             ft_is_alpha(char c);
int             ft_check_variable_definition(char *arg);
int             ft_check_export_args(t_command *command);
void            ft_print_exported_vars(t_env *envList);
int             ft_export(t_env **envlist, t_command *cmd);
// pwd
int 	        pwd(void);
// unset
int	            ft_unset(t_env **envList, t_command *cmd);

// EXECUTION

// builtin
int	            ft_is_builtin(t_command *cmd);
int	            ft_execute_builtin(t_command *cmd, t_env *envList);
// child
pid_t           ft_create_child_process();
void            ft_launch_child_processes(t_command *commands, int num_commands, int pipes[][2], pid_t child_pids[], t_env *envList, char **envp); // TO DO too much args
void            ft_execute_child_process(char *full_path, char **args, char **envp);
void            ft_wait_for_child_processes_to_end(pid_t *child_pids, int num_commands, char *full_path, char **args, char **envp);
void            ft_wait_for_child_process(pid_t pid);
void            ft_configure_child_process(t_command *commands, int num_commands, int index, int pipes[][2], t_env *envList, char **envp); // TO DO too much args
// command
int             ft_execute_single_command(t_command *command, t_commandList *commandList, t_env *envList, char **envp); 
void            ft_execute_external_command(t_command *command, t_commandList *commandList, char **envp); 
void            ft_printCommand(t_command *command);

// commandList
void            ft_initialize_commandList(t_commandList *commandList);
void            ft_execute_command_list(t_commandList *commandList, t_env *envList, char **envp); // TO DO t_global wtf 
void            ft_destroy_commandList(t_commandList *commandList);
void            ft_print_commandList(t_commandList *commandList);
// destroy
void            ft_destroy_command(t_commandList *commandList);
void	        ft_destroy_current_shell(t_mini *mini);
void            ft_destroy_commandList(t_commandList *commandList);
// history
void            ft_manage_history(t_mini *shell, const char *input);
void            ft_custom_prompt_msg(t_mini *shell);
// inputrc
char            *ft_create_inputrc_path();
int             ft_open_inputrc(const char *inputrc_path);
void            ft_write_inputrc_content(int fd);
void            ft_close_inputrc(int fd, char *inputrc_path);
void            ft_write_inputrc();
// path
char            *ft_build_full_path(t_commandList *commandList); 
void            ft_execute_command_with_relative_path(t_command *command);
void            ft_execute_command_with_path(t_command *command);
void            ft_execute_command_with_absolute_path(t_command *command);
char            *ft_lookfor_command_and_build_path(char *path, t_commandList *commandList);
// pipe
void            ft_execute_command_with_pipe(t_command *command, t_env *envList, char **envp);
void            ft_execute_piped_commands(t_commandList *commandList, t_command *commands, int num_commands, t_env *envList, char **envp);
// redirection
// shell
void            ft_exit_shell(t_mini *shell);
void            ft_initialize_environment(t_env **envList, char **env);
void            ft_initialize_minishell(t_mini *shell);
void            ft_execute_minishell(t_commandList *commandList, t_mini *shell, t_env *envList, char **envp);
// signal
void            ft_receive_signal_from_user(int signal_num);
void            ft_handle_signal_execution(int signal_num);
void            ft_init_signals(void(*signals_handle)(int));
void            ft_init_terminal_settings(void);
// tool_exec TO DO CLEAN IF NOT USED
char            *ft_strjoin_free(char const *s1, char const *s2, int free_s1);
t_env           *create_node2(char *var, char *value);
t_env           *ft_copy_env_list(t_env *src);
void            free_split(char **arr);

// LINKED LIST

// add
void            ft_add_to_list(t_env **envlist, t_env *new_node);
int	            ft_add_envVar_to_list(t_env **envlist, t_env *new_node, t_command *command);
void            ft_append_to_commandList(t_commandList *commandList, t_command *newNode);
void            ft_append_to_list_arg(t_command *command, char *arg);
void            ft_print_list(t_commandList *head, void (*printFunction)(void *data));

// clean
void            ft_free_list(t_commandList  *head);
void	        ft_free_array(char **array);
void            ft_delete_list(t_env *envlist);
void            ft_free_node(t_command  *node);
void            ft_free_env_node(t_env *new_node, t_env *tmp, char *str);
void            ft_delete_node(t_commandList **head, t_command *node);
void            ft_free_envList(t_env *envList);
// create
t_env           *ft_create_node_for_envList(char *var_array);
void            ft_init_new_node(t_commandList *commandList, t_command *command, char *token);
t_env           *ft_create_node_for_export_argument(char *name, char *value);
// duplicate
t_env	        *ft_envlist_duplicate(t_env **envlist);
t_env	        *ft_duplicate_node(char *name, char *value);
char            **ft_env_duplicate(char **envp);
// edit
void	        ft_replace_in_list(t_env *new_node, t_env **envlist);
void            ft_iterate_through_list_to_apply_function(t_commandList  *head, void (*callback)(void *data));
int             ft_compareString(void *data, void *target);
// list
int             ft_is_empty_list(t_commandList    *head);
int	            ft_is_in_list(char	*var, t_env **envlist);
int             ft_get_commandList_size(t_commandList  *head);
int	            ft_get_envList_size(t_env **list);
t_env	        *ft_get_in_list(char *var, t_env **envlist);
void            ft_print_generic(void *data);
// node
t_command       *ft_get_previous_node(t_commandList  *head, t_command  *node);
t_command       *ft_find_node(t_commandList  *head, void *target);
void	        ft_swap_nodes(t_env *tmp);
void            *ft_get_last_element_in_list(t_commandList *head);
t_env           *ft_find_envVar(t_env *envList, const char *targetName);

// PARSING

// custom_strtok TO DO CLEAN THIS
void            ft_print_word(const char *start, const char *end);
const char      *ft_find_next_delimiter(const char *start, char delimiter);
const char      *ft_find_closing_quote(const char *start);
void            ft_process_word(const char *start, const char *end);
void            ft_strtok_for_quotes(const char *input);
// error
int	            ft_check_if_its_any_white_space(char c);
t_Bool          ft_check_if_only_spaces(const char *str);
void            ft_initialization_of_errors(t_mini *shell);
void            ft_add_space_around_redirection(char *input);
// expansion
int             ft_is_valid_env_char(char c);
char            *ft_get_env_var_value(char *var_name);
int          ft_calculate_var_length(char *var_name, int g_exit_code);
int          ft_calculate_new_length(char *cmd, int g_exit_code);
void            ft_process_char(char *result, int *j, char *command, int *i);
char            *ft_expand_single_env_var(char *var_name);
char            *ft_expand_env_variables(char *command);

// parser
void            ft_process_the_first_token_as_a_command(t_commandList *commandList, char *token);
void            ft_process_token_as_an_argument(t_commandList *commandList, t_command *command, char *token);
int             ft_split_input_in_token_to_commandList(t_commandList *commandList, char *input);
int             ft_parse_and_add_to_commandList(t_commandList *commandList, char *input);
int             ft_launch_parsing_and_execution(t_commandList *commandList, char *input, t_env *envList, char **envp);
// pipe
void            ft_create_pipes(int pipes[2]);
void            ft_create_pipes_array(int pipes[][2], int num_pipes);
void            ft_close_pipes(int pipes[][2], int num_pipes);
int             ft_count_piped_commands(t_command *start_command);
// quote
int			    ft_is_quote(char c);
int			    ft_check_quotes_error(void);
void            ft_follow_quotes_state(t_command *cmd);
char            *ft_extract_quoted_argument(char *input);
void		    ft_tokenize_with_quotes(char *input);
void            ft_check_char_for_quote_type(char current_char, t_quote_type *quote_type); 
t_quote_type    ft_check_and_allocate_quote_type(char *token); 
// char         *ft_strtrim_with_quotes(char *str); where are you ?
// char         *ft_strtok_quoted(char *str, const char *delim); where are you ? 
// redirection
void            ft_redirect_stdout(t_command *command, char *input);
void            ft_redirect_stdin(t_command *command, char *input);
// token_type_check1
t_token_type    ft_check_pipe(char *token);
t_token_type    ft_check_heredoc(char *token); 
t_token_type    ft_check_lpr(char *token);
t_token_type    ft_check_rpr(char *token); 
t_token_type    ft_check_and(char *token);
// token_type_check2
t_token_type    ft_check_or(char *token);
t_token_type    ft_check_append(char *token); 
t_token_type    ft_check_out(char *token);
t_token_type    ft_check_in(char *token);
t_token_type    ft_check_not(char *token);
// token_type_check3
t_token_type    ft_check_end(char *token);
t_token_type    ft_check_command(char *token); 
t_token_type    ft_check_argument(char *token); 
t_token_type    ft_check_option(char *token); 
t_token_type    ft_check_unknown_type(char *token); 
// token
t_token_type    ft_checkType(TokenChecker checker, char *token);
t_token_type    ft_allocate_token_type(char *token);
// util TO DO CLEAN SI DEJA DANS LA LIBFT
char            *ft_strcpy(char *dest, const char *src);
char            *ft_strpbrk(const char *s1, const char *s2);
char            *ft_custom_strdup(const char *str);
char            *ft_strndup(const char *s, size_t n);

// GLOBAL

extern int	    g_exit_code;
void            rl_replace_line(const char *str, int i);

// MAIN
char            *ft_capture_input(void);
int             main(int ac, char **av, char **envp);
void	        ft_exit_shell(t_mini *shell);

#endif