/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:49:14 by obajja            #+#    #+#             */
/*   Updated: 2025/07/12 01:44:32 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*unquote_handler(char *input, int *i, t_mini *mini)
{
	int		start;
	char	*result;
	char	*temp;

	start = *i;
	while (input[*i] && !ft_is_whitespace(input[*i])
		&& input[*i] != '\'' && input[*i] != '"'
		&& !operator_check(&input[*i]))
		(*i)++;
	result = ft_strndup(&input[start], *i - start);
	if (!result)
		return (NULL);
	if (is_extendable(result, 0) != -1)
	{
		temp = ft_extender(result, mini->env, mini, 0);
		if (!temp)
			return (free (result), NULL);
		free (result);
		result = temp;
	}
	return (result);
}

char	*word_handler(char *input, int *i, t_mini *mini)
{
	char	*word;

	if (input[*i] == '\'' || input[*i] == '"')
	{
		word = quote_handler(input, i, mini->env, mini);
		if (!word)
			return (NULL);
		else
			return (word);
	}
	else
	{
		word = unquote_handler(input, i, mini);
		if (!word)
			return (NULL);
		else
			return (word);
	}
}
