/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:48:21 by obajja            #+#    #+#             */
/*   Updated: 2025/07/02 23:07:21 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_lex	*pipe_handler(t_parsing **node, t_lex *tokens, t_parsing *head)
{
	tokens = tokens->next;
	if (tokens == NULL)
	{
		write(2, "minishell: syntax error near unexpected token '|'\n", 50);
		free_parse(head);
		return (NULL);
	}
	(*node)->next = create_parse();
	if (!(*node)->next)
	{
		free_parse(head);
		return (NULL);
	}
	*node = (*node)->next;
	return (tokens);
}

t_parsing	*token_parser(t_lex *tokens, t_parsing    *head, t_parsing *node)
{
	if (!tokens)
		return (NULL);
	while (tokens)
	{
		if (!node)
		{
			node = create_parse();
			if (!node)
				return (NULL);
			head = node;
		}
		tokens = command_processor(node, tokens);
		if (node->cmd == NULL && node->infile == NULL && node->outfile == NULL
			&& node->append_out == NULL && node->heredoc_delim == NULL)
			return (free_parse(head), NULL);
		if (tokens == NULL)
			break ;
		if (tokens && tokens->type == TOKEN_PIPE)
			pipe_handler(&node, tokens, head);
	}
	node->next = NULL;
	return (head);
}