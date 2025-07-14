/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:47:04 by obajja            #+#    #+#             */
/*   Updated: 2025/07/14 11:42:00 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**create_args(char *first_arg)
{
	char	**all_args;

	all_args = ft_calloc(sizeof(char *), 2);
	if (!all_args)
		return (NULL);
	all_args[0] = ft_strdup(first_arg);
	if (!all_args[0])
		return (NULL);
	all_args[1] = NULL;
	return (all_args);
}

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
