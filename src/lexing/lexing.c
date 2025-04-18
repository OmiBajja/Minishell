/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:53:13 by obajja            #+#    #+#             */
/*   Updated: 2025/04/15 11:45:18 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *word_lexer(char *input, int *start)
{
	int		i;
	int		j;
	int		single_counter;
	int		double_counter;
	
	i = *start;
	j = *start;
	single_counter = 0;
	double_counter = 0;
	while (input[i])
	{
		if (!single_counter && !double_counter && ft_is_whitespace(input[i]))
			break;
		else if (!single_counter && input[i] == '"')
			double_counter = !double_counter;
		else if (!double_counter && input[i] == '\'')
			single_counter = !single_counter;
		else if (!single_counter && !double_counter && operator_check(input[i]))
			break;
		i++;
	}
	*start = i;
	if (i == j)
		return (NULL);
	return (ft_strndup(&input[j], i - j));
}
t_lex *lexing (char *input)
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
			word = word_lexer(input, &i);
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

void print_tokens(t_lex *tokens)
{
	if (!tokens)
		return;
	
	while (tokens) {
		if (tokens->value)
			printf("Token: [%s] Type: %d\n", tokens->value, tokens->type);
        tokens = tokens->next;
    }
	fflush(stdout);
}

