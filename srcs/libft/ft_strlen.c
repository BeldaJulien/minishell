/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienbelda <julienbelda@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:11:59 by bbessard          #+#    #+#             */
/*   Updated: 2023/12/01 12:56:18 by julienbelda      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
https://koor.fr/C/cstring/strlen.wp
*/

#include "libft.h"

size_t ft_strlen(const char *s)
{
    size_t len = 0;
    while (s[len] != '\0')
    {
        len++;
    }
    return len;
}

