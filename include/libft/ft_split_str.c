/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:52:55 by obajja            #+#    #+#             */
/*   Updated: 2025/06/28 07:59:48 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check_char(char src, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == src)
			return (1);
		i++;
	}
	return (0);
}

int	ft_count_words(char *src, char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (src[i] && ft_check_char(src[i], charset))
		i++;
	while (src[i])
	{
		if (src[i] && ft_check_char(src[i], charset))
		{
			if (src[i + 1] && !ft_check_char(src[i + 1], charset)
				&& src[i + 1] != 0)
				count++;
		}
		i++;
	}
	return (count);
}

int	ft_lenght_word(char *src, char *charset)
{
	int	i;
	int	a;
	int	z;

	i = 0;
	while (src[i] && ft_check_char(src[i], charset))
		i++;
	a = i;
	while (src[i] && !ft_check_char(src[i], charset))
		i++;
	z = i;
	i = z - a;
	return (i);
}

char	*ft_word_printer(char *src, char *charset)
{
	int		i;
	char	*tab;

	i = 0;
	tab = malloc((ft_lenght_word(src, charset) + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	while (src[i] && !ft_check_char(src[i], charset))
	{
		tab[i] = src[i];
		i++;
	}
	return (tab);
}

char	**ft_split_str(char *str, char *charset)
{
	char	**risotto;
	int		i;
	int		j;
	int		b;

	b = ft_count_words(str, charset) + 1;
	risotto = ft_calloc((b), sizeof(char *));
	if (!risotto)
		return (NULL);
	risotto[b - 1] = 0;
	j = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && ft_check_char(str[i], charset))
			i++;
		if (str[i] && !ft_check_char(str[i], charset))
		{
			risotto[j] = ft_word_printer(&str[i], charset);
			if (!risotto[j++])
				ft_freestrs(risotto);
		}
		i = i + ft_lenght_word(&str[i], charset);
	}
	return (risotto);
}

// int	main(void)
// {
// 	//char	*str =" Helloe Woerld dienosaeures ";
// 	char	*str ="Salut vous   allez\n les\frats\vhehe";
// 	char	*sep ="\f     \n\v";
// 	//char	*sep =" l,e";
// 	char	**pizza;
// 	int		i;

// 	pizza = ft_split_str(str,sep);
// 	i = 0;
// 	printf("mots : %d\n", ft_count_words(str, sep));
// 	//while (i < ft_count_words(str,sep))
// 	while (pizza[i])
// 	{
// 		printf("%s\n",pizza[i]);
// 		i++;
// 	}
//     ft_freestrs(pizza);
//     return (0);
// }