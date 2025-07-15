/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:53:13 by obajja            #+#    #+#             */
/*   Updated: 2025/07/15 17:08:50 by pafranci         ###   ########.fr       */
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
		else
			free (word);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}

static int	lex(int i, char *input, t_lex *tokens, t_mini *mini)
{
	int	op_len;

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
				return (-1);
		}
		else if (handle_word(&tokens, input, &i, mini))
			return (free_tokens(tokens), -1);
	}
	return (0);
}

t_lex	*lexing(char *input, t_mini *mini)
{
	t_lex	*tokens;
	int		i;

	i = 0;
	tokens = NULL;
	if (!input)
		return (NULL);
	while (ft_is_whitespace(input[i]))
		i++;
	if (input[i] == '|')
	{
		mini->status = 2;
		ft_printf_fd(2, "bash: syntax error near unexpected token `|'\n");
		return (NULL);
	}
	if (lex(i, input, tokens, mini) < 0)
		return (NULL);
	return (tokens);
}
