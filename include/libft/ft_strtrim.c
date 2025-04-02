/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:44:50 by obajja            #+#    #+#             */
/*   Updated: 2024/11/19 18:28:10 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_setchecker(char str, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == str)
			return (1);
		i++;
	}
	return (0);
}

static void	ft_starter(char const *str, char const *set, int *start, int *end)
{
	int	i;

	i = 0;
	if (str[i] && ft_setchecker(str[i], set))
	{
		while (str[i] && ft_setchecker(str[i], set))
			i++;
	}
	*start = i;
	while (str[i])
		i++;
	if (ft_setchecker(str[i - 1], set))
	{
		while (i > 0 && ft_setchecker(str[i - 1], set))
			i--;
	}
	*end = i;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int				start;
	int				end;
	unsigned int	test;
	char			*str;
	int				i;

	i = 0;
	ft_starter(s1, set, &start, &end);
	test = end - start;
	if (end < start)
		test = 0;
	str = malloc((test + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < end - start && test != 0)
	{
		str[i] = s1[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
#include <stdio.h>

int	main(void)
{
	//char	str[50]= " ,  .                    .  ";
	//char	set[13]= " .,";

	printf("%s", ft_strtrim("   xxx   xxx", " x"));
	return (0);
}*/