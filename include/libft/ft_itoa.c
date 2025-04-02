/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:32:18 by obajja            #+#    #+#             */
/*   Updated: 2024/11/14 19:11:26 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_mallocer(long *n, int *s)
{
	int		i;
	long	cpy;

	i = 1;
	if (*n < 0)
	{
		*n *= -1;
		i += 1;
		*s = 1;
	}
	else
		*s = 0;
	cpy = *n;
	while (cpy > 9)
	{
		cpy /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	ln;
	int		s;
	int		i;

	ln = n;
	i = ft_mallocer(&ln, &s);
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[i] = '\0';
	i--;
	while (i >= 0)
	{
		if (s == 1 && i == 0)
			str[0] = '-';
		else
			str[i] = ln % 10 + '0';
		ln /= 10;
		i--;
	}
	return (str);
}
/*
#include <stdio.h>

int	main(void)
{
	int n = 214483648;

	printf("%s", ft_itoa(n));
	return (0);
}*/