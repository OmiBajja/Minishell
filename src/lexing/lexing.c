/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:53:13 by obajja            #+#    #+#             */
/*   Updated: 2025/06/29 09:22:12 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	operator_handler(int op_len, t_lex	*tokens, char *input, int i)
{
	char	*operator;

	operator = ft_strndup(&input[i], op_len);
	add_to_list(&tokens, create_token(operator, find_operator(operator)));
	return (op_len);
}

char	*word_lexer(char *input, int *start, char **env)
{
	int		i;
	int		j;
	char	*result;

	i = *start;
	j = *start;
	if (input[i] == '"' || input[i] == '\'')
		return (quote_handler(input, start, env));
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
			break ;
		else if (operator_check(&input[i]) || ft_is_whitespace(input[i]))
			break ;
		i++;
	}
	*start = i;
	if (i == j)
		return (NULL);
	result = ft_strndup(&input[j], i - j);
	if (is_extendable(result) != -1)
		result = ft_extender(result, env);
	return (result);
}

t_lex	*lexing(char *input, char **env)
{
	t_lex	*tokens;
	char	*word;
	int		i;
	int		op_len;

	i = 0;
	tokens = NULL;
	if (!input)
		return (NULL);
	while (input[i])
	{
		while (ft_is_whitespace(input[i]))
			i++;
		op_len = operator_check(&input[i]);
		if (op_len)
			i += operator_handler(op_len, tokens, input, i);
		else
		{
			word = word_lexer(input, &i, env);
			if (word)
				add_to_list(&tokens, create_token(word, TOKEN_COMMAND));
			else
				return (NULL);
		}
	}
	return (tokens);
}

void	free_tokens(t_lex *tokens)
{
	t_lex	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}
