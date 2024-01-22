#include "minishell.h"

char *ft_strcpy(char *dest, const char *src)
{
    int i = 0;

    if (dest == NULL || src == NULL)
        return NULL;

    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';
    return dest;
}


char *ft_strpbrk(const char *s1, const char *s2)
{
    int i = 0;

    while (s1[i] != '\0')
    {
        int j = 0;
        while (s2[j] != '\0')
        {
            if (s1[i] == s2[j])
                return (char *)(s1 + i);
            j++;
        }
        i++;
    }
    return NULL;
}

char *ft_custom_strdup(const char *str) {
    size_t len = ft_strlen(str);
    char *copy = malloc(len + 1);

    if (copy == NULL) {
        perror("CHAOS, error allocating memory");
        exit(EXIT_FAILURE);
    }

    ft_strcpy(copy, str);
    return copy;
}

char *ft_strndup(const char *s, size_t n) 
{
    size_t len;
    size_t i;
    
    len = strlen(s);
    if (len > n) {
        len = n;
    }

    char *new_str = (char *)malloc(len + 1);
    if (new_str == NULL)
        return NULL; 

    i = 0;
    while (i < len)
    {
        new_str[i] = s[i];
        i++;
    }
    new_str[len] = '\0';
    return new_str;
}
