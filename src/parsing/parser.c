/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:48:21 by obajja            #+#    #+#             */
/*   Updated: 2025/07/15 14:49:40 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_lex	*pipe_handler(t_parsing **n, t_lex *t, t_parsing *h, t_mini *m)
{
	t = t->next;
	if (t == NULL)
	{
		m->status = 2;
		write(2, "minishell: syntax error near unexpected token '|'\n", 50);
		free_parse(h);
		return (NULL);
	}
	(*n)->next = create_parse();
	if (!(*n)->next)
	{
		free_parse(h);
		return (NULL);
	}
	*n = (*n)->next;
	return (t);
}

t_parsing	*token_parser(t_lex *tkn, t_parsing *h, t_parsing *n, t_mini *m)
{
	if (!tkn)
		return (NULL);
	while (tkn)
	{
		if (!n)
		{
			n = create_parse();
			if (!n)
				return (NULL);
			h = n;
		}
		tkn = command_processor(n, tkn, m);
		if (n->cmd == NULL && n->redirs == NULL)
			return (free_parse(h), NULL);
		if (tkn == NULL)
			break ;
		if (tkn && tkn->type == TOKEN_PIPE)
			tkn = pipe_handler(&n, tkn, h, m);
		if (!tkn)
			return (NULL);
	}
	n->next = NULL;
	return (h);
}
