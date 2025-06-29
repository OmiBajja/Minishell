/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:48:41 by pafranci          #+#    #+#             */
/*   Updated: 2025/06/29 11:09:39 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_pipex(int infile_fd, int **pipes, int cmd_count, pid_t *pid)
{
	int	i;

	i = 0;
	close(infile_fd);
	close_pipes(pipes, cmd_count - 1);
	while (i < cmd_count - 1)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
	free(pid);
}

void	wait_for_children(pid_t *pid, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}

t_parsing	*get_nth_node(t_parsing *head, int n)
{
	int	i;

	i = 0;
	while (head && i < n)
	{
		head = head ->next;
		i++;
	}
	return (head);
}

char	*find_env_paths(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strnstr(env[i], "PATH=", 5) && env[i][5])
			return (&env[i][5]);
	}
	return ("./");
}
