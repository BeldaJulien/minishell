#include "minishell.h"

int ft_is_valid_env_char(char c) 
{
    return !(isupper(c) || islower(c) || isdigit(c));
}


// DO NOT free if returning empty line resulting of getenv
char *ft_get_env_var_value(char *var_name) 
{
    char *value;

    if (!var_name) 
        return NULL;
    
    value = getenv(var_name);

    // Duplique la valeur pour éviter les problèmes avec la mémoire partagée
    if (value != NULL) 
        return ft_strdup(value);
    else 
        return NULL;
}

int ft_calculate_var_length(char *var_name, int g_exit_code) 
{
    char *status_str;
    char *var_value;
    int var_length;

    if (var_name == NULL) return 0;

    if (ft_strcmp(var_name, "?") == 0) 
    {
        // Cas spécial : $? (exit code)
        status_str = ft_itoa(g_exit_code);
        var_length = ft_strlen(status_str);
        free(status_str);
        return var_length;
    } else 
    {
        // Cas général : $variable
        printf("The var_name in ft_calculate_var_length sent to get_env_var_value is :'%s'\n", var_name);
        var_value = ft_get_env_var_value(var_name);
        if (var_value != NULL) 
        {
            var_length = ft_strlen(var_value);
            free(var_value);
        } 
        else
            var_length = 0;

        return var_length;
    }
}

// Fonction pour calculer la longueur totale après l'expansion des variables d'environnement
int ft_calculate_new_length(char *cmd, int g_exit_code) 
{    
    int i;
    int length;
    int start;
    
    if (cmd == NULL) 
        return 0;
    
    i = 0;
    length = 0;

    while (cmd[i] != '\0') {
        if (cmd[i] == '$') {
            i++;
            if (cmd[i] == '?') {
                length += ft_calculate_var_length("?", g_exit_code);
                i++;
            } else {
                start = i;
                while (cmd[i] != '\0' && ft_is_valid_env_char(cmd[i])) 
                    i++;

                length += ft_calculate_var_length(cmd + start, g_exit_code);
                printf("length is '%d'\n", length);
            }
        } else
            length++, i++;
    }

    return length;
}

void ft_process_char(char *result, int *j, char *command, int *i) 
{
    int start;
    char *var_name;
    char *expanded_var;

    if (command[*i] == '$') 
    {
        (*i)++;
        start = *i;

        // Trouver le nom de la variable
        printf("The command in ft_process_char before strndup is :'%s'\n", command);
        while (command[*i] != '\0' && ft_is_valid_env_char(command[*i])) (*i)++;
        // Wow this -1 has been painfull.
        var_name = ft_strndup(command + start, *i - start - 1);
        printf("The var_name in ft_process_char after strndup is :'%s'\n", var_name);

        // Expansion de la variable d'environnement
        expanded_var = ft_expand_single_env_var(var_name);
        printf("The expanded_var in ft_process_char after ft_expand_single_env_var(var_name) is :'%s'\n", expanded_var);

        // Concaténer la variable d'environnement étendue au résultat
        // ft_strcat(result, expanded_var);
        free(var_name);
        ft_strcpy(result + *j, expanded_var);
        *j += ft_strlen(expanded_var);
        write(STDOUT_FILENO, expanded_var, ft_strlen(expanded_var));

        // Libérer la mémoire
        
        free(expanded_var);
    } else {
        result[*j] = command[*i];
        (*j)++;
        (*i)++;
    }
}

char *ft_expand_single_env_var(char *var_name) 
{
    char *value;

    // if (!var_name) return ft_strdup("");  // Retourne une chaîne vide si le nom de la variable est NULL

    printf("The var_name in ft_expand_single_env_varp is :'%s'\n", var_name);

    value = ft_get_env_var_value(var_name);

    printf("The value return value = ft_get_env_var_value is :'%s'\n", value);

    if (!value) 
        return ft_strdup("");  // Retourne une chaîne vide si la valeur de la variable n'est pas trouvée

    return value;
}

char *ft_expand_env_variables(char *command)
 {
    if (!command) return NULL;

    int i = 0, j = 0;
    int new_length = ft_calculate_new_length(command, g_exit_code);
    char *result = (char *)malloc(new_length + 1);

    if (!result) 
        return NULL;

    while (command[i] != '\0') {
        ft_process_char(result, &j, command, &i);
    }

    result[j] = '\0';
    return result;
}

