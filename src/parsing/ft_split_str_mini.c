/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str_mini.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:52:55 by obajja            #+#    #+#             */
/*   Updated: 2025/04/09 23:54:34 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_check_char(char src, char *charset, t_mini  *mini)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == src)
		{
			if (charset[i] == '|')
				mini->data->outfile[0] = "|";
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_count_words(char *src, char *charset, t_mini  *mini)
{
	int	i;
	int	count;

	(void) mini;
	i = 0;
	count = 0;
	while (src[i] && ft_check_char(src[i], charset, mini))
		i++;
	while (src[i])
	{
		if (src[i] && ft_check_char(src[i], charset, mini))
		{
			if (src[i + 1] && !ft_check_char(src[i + 1], charset, mini)
				&& src[i + 1] != 0)
				count++;
		}
		i++;
	}
	return (count);
}

int	ft_lenght_word(char *src, char *charset, t_mini  *mini)
{
	int	i;
	int	a;
	int	z;

	(void) mini;
	i = 0;
	while (src[i] && ft_check_char(src[i], charset, mini))
		i++;
	a = i;
	while (src[i] && !ft_check_char(src[i], charset, mini))
		i++;
	z = i;
	i = z - a;
	return (i);
}

char	*ft_word_printer(char *src, char *charset, t_mini  *mini)
{
	int		i;
	char	*tab;

	(void) mini;
	i = 0;
	tab = malloc((ft_lenght_word(src, charset, mini) + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	while (src[i] && !ft_check_char(src[i], charset, mini))
	{
		tab[i] = src[i];
		i++;
	}
	return (tab);
}

char	**ft_split_str_mini(char *str, char *charset, t_mini  *mini)
{
	char	**risotto;
	int		i;
	int		j;
	int		b;
	
	(void) mini;
	b = ft_count_words(str, charset, mini) + 1;
	risotto = malloc((b) * sizeof(char *));
	if (!risotto)
		return (NULL);
	risotto[b - 1] = 0;
	j = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && ft_check_char(str[i], charset, mini))
			i++;
		if (str[i] && !ft_check_char(str[i], charset, mini))
			risotto[j] = ft_word_printer(&str[i], charset, mini);
		if (!risotto[j])
			ft_freestrs(risotto);
		j++;
		i = i + ft_lenght_word(&str[i], charset, mini);
	}
	risotto[j] = 0;
	return (risotto);
}
