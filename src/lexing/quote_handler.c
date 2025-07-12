/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:30:23 by obajja            #+#    #+#             */
/*   Updated: 2025/07/12 03:06:45 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*single_quote_handler(char *input, int *index)
{
	char	*quote;
	int		fin;

	fin = *index;
	while (input[++fin])
	{
		if (input[fin] == '\'')
		{
			quote = ft_strndup(&input[*index], fin - *index);
			if (!quote)
				return (NULL);
			quote = ft_dequoter(quote);
			*index = fin + 1;
			return (quote);
		}
	}
	*index = fin;
	ft_printf_fd(2, "You forgot quotes not cool\n");
	return (NULL);
}

char	*double_quote_handler(char *input, int *index, char **env, t_mini *mini)
{
	char	*quote;
	char	*temp;
	int		fin;

	fin = *index;
	while (input[++fin])
	{
		if (input[fin] == '"')
		{
			temp = ft_strndup(&input[*index], fin - *index);
			if (!temp)
				return (NULL);
			if (is_extendable(temp, 1) != -1)
			{
				quote = ft_extender(temp, env, mini, 1);
				free(temp);
				temp = quote;
			}
			quote = ft_dequoter(temp);
			*index = fin + 1;
			return (quote);
		}
	}
	*index = fin;
	return (ft_printf_fd(2, "You forgot quotes not cool\n"), NULL);
}

char	*quote_handler(char *input, int *index, char **env, t_mini *mini)
{
	char	*quote;

	if (input[*index] == '\'')
		quote = single_quote_handler(input, index);
	else if (input[*index] == '"')
		quote = double_quote_handler(input, index, env, mini);
	else
		quote = NULL;
	return (quote);
}
