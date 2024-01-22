#include "minishell.h"

void ft_putchar(char c)
{
    write (1, &c, 1);
}

void ft_print_word(const char *start, const char *end) 
{
    while (start < end) 
    {
        ft_putchar(*start);
        start++;
    }
}

const char *ft_find_next_delimiter(const char *start, char delimiter) 
{
    while (*start && *start != delimiter) 
    {
        start++;
    }
    return start;
}

const char *ft_find_closing_quote(const char *start) 
{
    start++;  // Ignorer le guillemet ouvrant
    while (*start && *start != '"') 
    {
        start++;
    }
    return start;
}

void ft_process_word(const char *start, const char *end) 
{
    if (*start == '"') 
    {
        const char *closing_quote = ft_find_closing_quote(start);
        ft_print_word(start, closing_quote);

        if (*start == '"') 
        {
            ft_putchar(*start);  // Imprimer le guillemet fermant
        }
    } else {
        ft_print_word(start, end);
    }
}

void ft_strtok_for_quotes(const char *input) 
{
    const char *start;
    const char *end;
    
    start = input;
    while (*start) 
    {
        start = ft_find_next_delimiter(start, ' ');
        while (*start && (*start == ' ' || *start == '\t')) 
        {
            ft_putchar(*start);
            start++;
        }

        end = ft_find_next_delimiter(start, ' ');

        ft_process_word(start, end);

        ft_putchar('\n');
        start = end;
    }
}
