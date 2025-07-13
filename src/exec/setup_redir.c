/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:21:17 by pafranci          #+#    #+#             */
/*   Updated: 2025/07/13 13:18:47 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	apply_pipe_redirs(t_child *child)
{
	if (child->cmd_count <= 1)
		return ;
	if (child->i > 0)
	{
		if (dup2(child->pipes[child->i - 1][0], STDIN_FILENO) < 0)
			perror_exit();
	}
	if (child->i < child->cmd_count - 1)
	{
		if (dup2(child->pipes[child->i][1], STDOUT_FILENO) < 0)
			perror_exit();
	}
}

int	setup_redirs_list(t_redir *r, t_child *child, t_mini *mini)
{
	int		fd;

	(void)mini;
	(void)child;
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
			return (1);
		}
		if (r->type == TOKEN_REDIR_IN || r->type == TOKEN_HEREDOC_IN)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		r = r->next;
	}
	return (0);
}

static void	apply_default_infile(t_child *child, t_parsing *cmd)
{
	int	fd;

	if (child->i != 0 || cmd->redirs != NULL)
		return ;
	fd = open(child->infile_path, O_RDONLY);
	if (fd < 0)
		perror_exit();
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	apply_redirs(t_child *child, t_parsing *cmd, t_mini *mini)
{
	apply_pipe_redirs(child);
	if (setup_redirs_list(cmd->redirs, child, mini) != 0)
	{
		master_cleaner(mini, child);
		exit(EXIT_FAILURE);
	}
	apply_default_infile(child, cmd);
}
