/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_epur_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:07:27 by bbessard          #+#    #+#             */
/*   Updated: 2023/10/21 15:10:17 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_epur_str(const char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\t')
				flag = 1;
		else 
		{
			if (flag == 1)
			{
				write (1, " ", 1);
				flag = 0;
			}
			write (1, &str[i], 1);
		}
		i++;
	}
	return NULL;
}
