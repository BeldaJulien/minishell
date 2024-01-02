/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprime.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:10:09 by bbessard          #+#    #+#             */
/*   Updated: 2023/10/21 14:16:55 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	main(int ac, char **av)
{
	int	nbr;
	int	i;

	nbr = atoi(av[1]);
	if (ac == 2)
	{
		i = 1;
		if (nbr == 1)
			printf("1");
		while (++i <= nbr)
		{
			if (nbr % i == 0)
			{
				printf ("%d", i);
				if (nbr == i)
					break ;
				printf("*");
				nbr /= i;
				i = 1;
			}
		}
	}
	printf ("\n");
	return (0);
}
