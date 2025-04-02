/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:43:20 by obajja            #+#    #+#             */
/*   Updated: 2025/02/12 13:15:30 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_strlen(char const *s);

static int	ft_countwords(char const *s, char c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (s[0] != '\0' && s[0] != c)
		j++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
				j += 1;
		i++;
	}
	return (j);
}

void	ft_freestrs(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free (tab);
	return ;
}

static char	*ft_wordprinter(char const *s, char c)
{
	int		i;
	char	*tab;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	tab = malloc((i + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	tab[i] = '\0';
	i--;
	while (i >= 0 && s[i])
	{
		tab[i] = s[i];
		i--;
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;

	j = 0;
	i = ft_strlen(s);
	tab = malloc((ft_countwords(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (j < ft_countwords(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		tab[j] = ft_wordprinter(&s[i], c);
		if (!tab[j])
			ft_freestrs(tab);
		j++;
		while (s[i] && s[i] != c)
			i++;
	}
	tab[j] = NULL;
	j = 0;
	return (tab);
}
/*
int	main(void)
{
	char	str[100]= " hel lo! ";
	char	sep = ' ';
	
	char **tab = ft_split(str, sep);
	free(tab);
	return (0);
}*/
/*	j = 0;
	while (tab[j])
	{
		printf("\n%s", tab[j]);
		j++;
	}
	return (tab);
}*/