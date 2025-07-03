/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:53:13 by obajja            #+#    #+#             */
/*   Updated: 2025/07/03 15:30:10 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*operator_handler(int op_len, char *input, int i)
{
	return (ft_strndup(&input[i], op_len));
}

char	*word_lexer(char *input, int *start, char **env, t_mini *mini)
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
		result = ft_extender(result, env, mini);
	return (result);
}

static void	handle_operator(t_lex **tokens, const char *input, int *i)
{
	int		op_len;
	char	*op_str;

	op_len = operator_check(&input[*i]);
	op_str = ft_strndup(&input[*i], op_len);
	add_to_list(tokens, create_token(op_str, find_operator(op_str)));
	*i += op_len;
}

static int	handle_word(t_lex **tokens, char *input, int *i, t_mini *mini)
{
	char	*word;

	word = word_lexer(input, i, mini->env, mini);
	if (word)
	{
		add_to_list(tokens, create_token(word, TOKEN_COMMAND));
		return (1);
	}
	return (0);
}

t_lex	*lexing(char *input, t_mini *mini)
{
	t_lex	*tokens;
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
		if (!input[i])
			break ;
		op_len = operator_check(&input[i]);
		if (op_len)
			handle_operator(&tokens, input, &i);
		else if (!handle_word(&tokens, input, &i, mini))
		{
			free_tokens(tokens);
			return (NULL);
		}
	}
	return (tokens);
}
