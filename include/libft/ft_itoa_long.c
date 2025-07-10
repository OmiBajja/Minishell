/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 20:15:37 by obajja            #+#    #+#             */
/*   Updated: 2025/07/10 20:51:11 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_mallocer(long long *n, long long *s)
{
	long long	i;
	long long	cpy;

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

char	*ft_itoa_long(long long n)
{
	char		*str;
	long long	ln;
	long long	s;
	long long	i;

	ln = n;
	if (n == -9223372036854775807LL - 1)
		return (ft_strdup("-9223372036854775808"));
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
