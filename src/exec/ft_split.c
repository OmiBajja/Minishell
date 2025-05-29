/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:42:46 by pafranci          #+#    #+#             */
/*   Updated: 2025/05/29 02:23:18 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_wordcount(char const *s, char c)
{
	bool	is_word;
	int		wc;

	wc = 0;
	is_word = false;
	while (*s)
	{
		if (*s == c)
		{
			if (is_word)
				is_word = false;
		}
		else
		{
			if (!is_word)
			{
				wc++;
				is_word = true;
			}
		}
		s++;
	}
	return (wc);
}

static int	ft_word_len(const char *s, int start, char c)
{
	int	wlen;

	wlen = 0;
	while (s[start + wlen] != c && s[start + wlen])
		wlen++;
	return (wlen);
}

static int	ft_gap_len(const char *s, int start, char c)
{
	int	glen;

	glen = 0;
	while (s[start + glen] == c)
		glen++;
	return (glen);
}

static void	ft_free_split(char **res, int wi)
{
	while (wi-- > 0)
		free(res[wi]);
	free(res);
}

char	**ft_split_pau(char const *s, char c)
{
	int		i;
	int		wi;
	int		wc;
	char	**res;

	wc = ft_wordcount(s, c);
	res = (char **)malloc((wc + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	wi = -1;
	while (++wi < wc)
	{
		i += ft_gap_len(s, i, c);
		res[wi] = ft_substr(s, i, ft_word_len(s, i, c));
		if (!res[wi])
			return (ft_free_split(res, wi), NULL);
		i += ft_word_len(s, i, c);
	}
	res[wc] = NULL;
	return (res);
}
/*
int	main()
{
	char **str;
	int	i;
	str = ft_split_pau("salut salut bonjour sadjasdjaiosjd", ' ');
	i = 0;
	while(str[i])
	{
		printf("%s\n", str[i]);
		free(str[i]);
		i++;
	}
	free(str);
}
int	main(void)
{
	char str[] = "Tripouille hell    yeas";

	char **res = ft_split_pau(str, ' ');
	int x = -1;
	while (res[++x])
	{
		printf("The word is: %s\n", res[x]);
		free(res[x]);
	}
	free(res);
	return (0);
}
*/