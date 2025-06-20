/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:53:13 by obajja            #+#    #+#             */
/*   Updated: 2025/06/11 21:21:15 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *word_lexer(char *input, int *start, char **env)
{
	int		i;
	int		j;
	char	*result;

	i = *start;
	j = *start;
	if (input[i] == '"' || input[i] == '\'')
		return(quote_handler(input, start, env));
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
			break;
		else if (operator_check(input[i]) || ft_is_whitespace(input[i]))
			break;
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
t_lex *lexing (char *input, char **env)
{
	t_lex 	*tokens;
	char	operator;
	char	*word;
	int		i;

	i = 0;
	tokens = NULL;
	while (input[i])
	{
		while (ft_is_whitespace(input[i]))
			i++;
		if (operator_check(input[i]))
		{
			operator = input[i++];
			add_to_list(&tokens, create_token(ft_strndup(&operator, 1), find_operator(operator)));
		}
		else
		{
			word = word_lexer(input, &i, env);
			if (word)
				add_to_list(&tokens, create_token(word, TOKEN_COMMAND));
		}
	}
	return (tokens);
}

void free_tokens(t_lex *tokens)
{
    t_lex *tmp;

    while (tokens)
    {
        tmp = tokens->next;
        free(tokens->value);
        free(tokens);
        tokens = tmp;
    }
}
