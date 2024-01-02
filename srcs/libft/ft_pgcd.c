/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pgcd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:58:55 by bbessard          #+#    #+#             */
/*   Updated: 2023/10/21 15:08:18 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**  Plus Grand Common Divider = PGCD
*/

#include "libft.h"

unsigned int ft_pgcd(unsigned int a, unsigned int b)
{
	unsigned int	tmp;
	
	if (a <= 0 || b <= 0)
	{
		printf("\n");
		return (0);
	}
	while (b != 0)
	{
		tmp = b;
		b = a % b;
		a = tmp;
	}
	return a;
}
