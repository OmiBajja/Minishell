/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:53:13 by obajja            #+#    #+#             */
/*   Updated: 2025/07/02 18:54:18 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	operator_handler(int op_len, t_lex *tokens, char *input, int i)
{
	char	*operator;

	operator = ft_strndup(&input[i], op_len);
	add_to_list(&tokens, create_token(operator, find_operator(operator)));
	return (op_len);
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

static int	handle_input(t_lex **tokens,
						char *input,
						int *i,
						t_mini_env *mini_env)
{
	int		op_len;
	char	*word;

	op_len = operator_check(&input[*i]);
	if (op_len)
		*i = operator_handler(op_len, *tokens, input, *i);
	else
	{
		word = word_lexer(input, i, mini_env->env, mini_env->mini);
		if (!word)
			return (0);
		add_to_list(tokens, create_token(word, TOKEN_COMMAND));
	}
	return (1);
}

t_lex	*lexing(char *input, char **env, t_mini *mini)
{
	t_lex		*tokens;
	int			i;
	t_mini_env	mini_env;

	if (!input)
		return (NULL);
	mini_env.env = env;
	mini_env.mini = mini;
	tokens = NULL;
	i = 0;
	while (input[i])
	{
		while (ft_is_whitespace(input[i]))
			i++;
		if (!input[i])
			break ;
		if (!handle_input(&tokens, input, &i, &mini_env))
			return (NULL);
	}
	return (tokens);
}

void	free_tokens(t_lex *tokens)
{
	t_lex	*tmp;

	while (tokens)
	{
		if (tokens->value)
			free_null(tokens->value);
		if (tokens->next)
		{
			tmp = tokens->next;
			free(tokens);
			tokens = tmp;
		}
		else
		{
			free(tokens);
			break ;
		}
	}
	tokens = NULL;
}
