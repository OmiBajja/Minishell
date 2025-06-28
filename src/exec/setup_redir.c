/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:21:17 by pafranci          #+#    #+#             */
/*   Updated: 2025/06/28 12:27:12 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	setup_input(t_child *child, t_parsing *cmd)
{
	int	fd;

	if (cmd->heredoc_file)
	{
		fd = open(cmd->heredoc_file, O_RDONLY);
		if (fd < 0)
			perror_exit();
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (child->i == 0)
		dup2(child->infile_fd, STDIN_FILENO);
	else
		dup2(child->pipes[child->i - 1][0], STDIN_FILENO);
}

void	setup_output(t_child *child, t_parsing *cmd)
{
	int	fd;
	if (child->i == child->cmd_count - 1)
	{
		if (cmd->append_out)
			fd = open(cmd->append_out, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (cmd->outfile)
			fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd >= 0)
		{
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
	}
	else
		dup2(child->pipes[child->i][1], STDOUT_FILENO);
}
