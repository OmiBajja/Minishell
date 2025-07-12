/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:57:19 by obajja            #+#    #+#             */
/*   Updated: 2025/07/12 01:14:16 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	operator_check(const char *input)
{
	if (!input || !*input)
		return (0);
	else if ((input[0] == '<' || input[0] == '>') && input[0] == input[1])
		return (2);
	else if (input[0] == '|' || input[0] == '<' || input[0] == '>')
		return (1);
	else
		return (0);
}

int	find_operator(const char *str)
{
	if (!ft_strcmp(str, "|"))
		return (TOKEN_PIPE);
	else if (!ft_strcmp(str, "<<"))
		return (TOKEN_HEREDOC_IN);
	else if (!ft_strcmp(str, ">>"))
		return (TOKEN_APPEND_OUT);
	else if (!ft_strcmp(str, "<"))
		return (TOKEN_REDIR_IN);
	else if (!ft_strcmp(str, ">"))
		return (TOKEN_REDIR_OUT);
	else
		return (TOKEN_UNKOWN);
}

t_lex	*create_token(char *value, int type)
{
	t_lex	*token;

	token = ft_calloc(sizeof(t_lex), 1);
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

int	add_to_list(t_lex **head, t_lex *new)
{
	t_lex	*temp;

	if (!new)
		return (EXIT_FAILURE);
	if (!*head)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	new->next = NULL;
	return (EXIT_SUCCESS);
}

void	print_tokens(t_lex *tokens)
{
	if (!tokens)
		return ;
	while (tokens)
	{
		if (tokens->value)
			printf("Token: [%s] Type: %d\n", tokens->value, tokens->type);
		tokens = tokens->next;
	}
}
