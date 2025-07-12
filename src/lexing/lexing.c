/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:53:13 by obajja            #+#    #+#             */
/*   Updated: 2025/07/12 01:18:32 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*operator_handler(int op_len, char *input, int i)
{
	return (ft_strndup(&input[i], op_len));
}

char	*word_lexer(char *input, int *start, t_mini *mini)
{
	int		i;
	char	*result;
	char	*quotes;
	char	*temp;

	i = *start;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (input[i] && !operator_check(&input[i])
		&&!ft_is_whitespace(input[i]))
	{
		quotes = word_handler(input, &i, mini);
		if (!quotes)
			return (free (result), NULL);
		temp = ft_strjoin(result, quotes);
		if (!temp)
			return (free (result), free (quotes), NULL);
		free (result);
		free (quotes);
		result = temp;
	}
	*start = i;
	return (result);
}

static int	handle_operator(t_lex **tokens, const char *input, int *i)
{
	int		op_len;
	char	*op_str;

	op_len = operator_check(&input[*i]);
	op_str = ft_strndup(&input[*i], op_len);
	if (!op_str)
		return (EXIT_FAILURE);
	if (add_to_list(tokens, create_token(op_str, find_operator(op_str))))
		return (EXIT_FAILURE);
	*i += op_len;
	return (EXIT_SUCCESS);
}

static int	handle_word(t_lex **tokens, char *input, int *i, t_mini *mini)
{
	char	*word;

	word = word_lexer(input, i, mini);
	if (word)
	{
		if (ft_strncmp(word, "", 1))
		{
			if (add_to_list(tokens, create_token(word, TOKEN_COMMAND)))
				return (EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}

t_lex	*lexing(char *input, t_mini *mini)
{
	t_lex	*tokens;
	int		op_len;
	int		i;

	i = 0;
	tokens = NULL;
	if (!input)
		return (NULL);
	while (input[i])
	{
		while (ft_is_whitespace(input[i]))
			i++;
		if (!input[i])
			break ;
		op_len = operator_check(&input[i]);
		if (op_len)
		{
			if (handle_operator(&tokens, input, &i))
				return (NULL);
		}
		else if (handle_word(&tokens, input, &i, mini))
			return (free_tokens(tokens), NULL);
	}
	return (tokens);
}
