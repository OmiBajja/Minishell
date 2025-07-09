/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:21:17 by pafranci          #+#    #+#             */
/*   Updated: 2025/07/08 18:27:14 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	setup_redirs_list(t_redir *r)
{
	int		fd;

	while (r)
	{
		if (r->type == TOKEN_REDIR_IN || r->type == TOKEN_HEREDOC_IN)
			fd = open(r->file, O_RDONLY);
		else if (r->type == TOKEN_APPEND_OUT)
			fd = open(r->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(r->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror(r->file);
			exit(1);
		}
		if (r->type == TOKEN_REDIR_IN || r->type == TOKEN_HEREDOC_IN)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		r = r->next;
	}
}

void	apply_redirs(t_child *child, t_parsing *cmd)
{
	int	fd;
	int	i;
	int	**pipes;
	int	cmd_count;

	i = child->i;
	cmd_count = child->cmd_count;
	pipes = child->pipes;
	if (cmd_count > 1)
	{
		if (i > 0)
		{
			if (dup2(pipes[i - 1][0], STDIN_FILENO) < 0)
				perror_exit();
		}
		if (i < cmd_count - 1)
		{
			if (dup2(pipes[i][1], STDOUT_FILENO) < 0)
				perror_exit();
		}
	}
	setup_redirs_list(cmd->redirs);
	if (i == 0 && !cmd->redirs)
	{
		fd = open(child->infile_path, O_RDONLY);
		if (fd < 0)
		{
			perror(child->infile_path);
			exit(1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	
}
