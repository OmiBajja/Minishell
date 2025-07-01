/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:48:41 by pafranci          #+#    #+#             */
/*   Updated: 2025/07/01 15:13:12 by pafranci         ###   ########.fr       */
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

void	wait_for_children(pid_t *pid, int cmd_count, t_mini *mini)
{
	int		waited;
	int		status;
	int		sig;
	pid_t	wpid;

	waited = 0;
	while (waited < cmd_count)
	{
		wpid = wait(&status);
		if (wpid == -1)
			break ;
		waited++;
		if (wpid == pid[cmd_count - 1])
		{
			if (WIFEXITED(status))
				mini->status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				mini->status = 128 + sig;
				if (sig == SIGINT || sig == SIGQUIT)
					write(STDOUT_FILENO, "\n", 1);
			}
		}
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
