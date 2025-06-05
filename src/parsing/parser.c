/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:48:21 by obajja            #+#    #+#             */
/*   Updated: 2025/04/15 17:04:18 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_parsing *token_parser(char *input, t_lex *tokens, char **env)
{
    t_parsing *head;
	t_parsing *node;

	head = NULL;
	node = NULL;
	(void)input;
	while (tokens)
	{
		if (!node)
		{
			node = create_parse();
			head = node;
		}
		tokens = command_processor(node, tokens, env);
		if (tokens && tokens->type == TOKEN_PIPE)
		{
			tokens = tokens->next;
			node->next = create_parse();
			node = node->next;
		}
	}
	return (head);
}
