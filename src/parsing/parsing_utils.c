/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:47:04 by obajja            #+#    #+#             */
/*   Updated: 2025/07/08 15:31:55 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_null(char *to_free)
{
	if (to_free)
	{
		free(to_free);
		to_free = NULL;
	}
}

void	print_command(t_parsing *cmd)
{
	int	i;

	i = 0;
	printf("=== COMMAND ===\n");
	if (cmd->cmd)
		printf("Command: %s\n", cmd->cmd);
	else
		printf("Command: (null)\n");
	printf("Args: ");
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			printf("[%s] ", cmd->args[i]);
			i++;
		}
	}
	else
		printf("(null)");
	printf("\n");
	printf("================\n\n");
}

void	print_all_commands(t_parsing *head)
{
	while (head)
	{
		printf("== PIPE ==\n");
		print_command(head);
		head = head->next;
	}
}

void	free_parse(t_parsing *parse)
{
	t_parsing	*tmp;
	t_redir		*r;
	t_redir		*next;

	while (parse)
	{
		if (parse->cmd)
			free_null(parse->cmd);
		if (parse->args)
			ft_freestrs(parse->args);
		tmp = parse->next;
		r = parse->redirs;
		while (r)
		{
			next = r->next;
			if (r->file)
				free(r->file);
			free(r);
			r = next;
		}
		free(parse);
		parse = tmp;
	}
	parse = NULL;
}
