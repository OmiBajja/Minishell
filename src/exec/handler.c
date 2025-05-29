/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:53:35 by pafranci          #+#    #+#             */
/*   Updated: 2025/05/29 02:04:22 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exec_handler(t_parsing *head, char **envp)
{
	t_parsing	*node;
	char		**cmds;
	char		*infile;
	char		*outfile;
	int			cmd_count;
	int			i;
	int			j;
	int			len;

	cmd_count = 0;
	node = head;
	infile = head->infile;
	while (node)
	{
		cmd_count++;
		if (node->outfile)
			outfile = node->outfile;
		node = node->next;
	}
	cmds = malloc((cmd_count + 1) * sizeof(char *));
	if (!cmds)
		return;
	node = head;
	i = 0;
	while (node)
	{
		j = 0;
		len = 0;
		while (node->args[j])
		{
			len += ft_strlen(node->args[j]) + 1;
			j++;
		}
		cmds[i] = malloc(len + 1);
		if (!cmds[i])
		{
			perror("malloc");
			exit(1);
		}
		cmds[i][0] = '\0';
		j = 0;
		while (node->args[j])
		{
			strcat(cmds[i], node->args[j]);
			if (node->args[j + 1])
				strcat(cmds[i], " ");
			j++;
		}
		i++;
		node = node->next;
	}
	cmds[i] = NULL;
	pipex(infile, outfile, cmds, cmd_count, envp);
	i = 0;
	while (i < cmd_count)
	{
		free(cmds[i]);
		i++;
	}
	free(cmds);
}