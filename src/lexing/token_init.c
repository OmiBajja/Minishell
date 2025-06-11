/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:57:19 by obajja            #+#    #+#             */
/*   Updated: 2025/06/11 11:51:42 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	operator_check(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	else
		return (0);
}

int	find_operator(char c)
{
	if (c == '|')
		return (TOKEN_PIPE);
	if (c == '<')
		return (TOKEN_REDIR_IN);
	if (c == '>')
		return (TOKEN_REDIR_OUT);
	else
		return (TOKEN_UNKOWN);
}

t_lex *create_token(char *value, int type)
{
	t_lex *token;
	
	token = malloc(sizeof(t_lex));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

void add_to_list(t_lex **head, t_lex *new)
{
	t_lex *temp;

	if (!*head)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
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
	//fflush(stdout);
}
