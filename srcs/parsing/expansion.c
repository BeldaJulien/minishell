#include "minishell.h"

int ft_is_valid_env_char(char c) {
    return ft_isalpha(c) || (c == '_');
}

// DO NOT free if returning empty line resulting of getenv
char *ft_getenv_var_value(const char *name) {
    char *value;
    
    value = getenv(name);
    if (value != NULL) {
        return value;
    } else {
        return "";
    }
}

int ft_calculate_new_length(const char *cmd, int g_exit_code) {
    int length = 0;
    int i = 0;

    while (cmd[i] != '\0') {
        if (cmd[i] == '$') {
            i++;
            if (cmd[i] == '?') {
                char *status_str = ft_itoa(g_exit_code);
                length += ft_strlen(status_str);
                free(status_str);
                i++;
            } else {
                int start = i;
                while (cmd[i] != '\0' && ft_is_valid_env_char(cmd[i])) i++;
                char *var_name = ft_strndup(cmd + start, i - start);
                char *var_value = ft_getenv_var_value(var_name);
                length += ft_strlen(var_value);
                free(var_name);
            }
        } else {
            length++;
            i++;
        }
    }
    return length;
}

char *ft_expand_env_variables(t_command *command, int g_exit_code) 
{
    if (!command) return NULL;

    char *result = malloc(ft_calculate_new_length(command->name, g_exit_code) + 1);
    if (!result) return NULL;

    int i = 0, j = 0;
    while (command->name[i] != '\0') {
        if (command->name[i] == '$' && command->quoteType != SINGLE_QUOTE) {
            i++;
            char *var_value;
            if (command->name[i] == '?') {
                var_value = ft_itoa(g_exit_code);
                i++;
            } else {
                int start = i;
                while (command->name[i] != '\0' && ft_is_valid_env_char(command->name[i])) i++;
                char *var_name = ft_strndup(command->name + start, i - start);
                var_value = ft_getenv_var_value(var_name);
                free(var_name);
            }
            ft_strcpy(result + j, var_value);
            j += ft_strlen(var_value);
            free(var_value);
        } else {
            result[j] = command->name[i];
            j++;
            i++;
        }
    }
    result[j] = '\0';
    return result;
}
