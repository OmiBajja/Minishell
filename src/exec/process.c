/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:24:19 by pafranci          #+#    #+#             */
/*   Updated: 2025/07/03 14:32:28 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	**create_pipes(int n)
{
	int	**pipes;
	int	i;

	pipes = ft_calloc(n, sizeof (int *));
	if (!pipes)
		return (perror_exit(), NULL);
	i = 0;
	while (i < n)
	{
		pipes[i] = ft_calloc(2, sizeof (int));
		if (!pipes[i])
			perror_exit();
		if (pipe(pipes[i]) < 0)
			perror_exit();
		i++;
	}
	return (pipes);
}

void	close_pipes(int **pipes, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	child_process(t_child *child, t_mini *mini)
{
	t_parsing	*cmd;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	cmd = get_nth_node(child->cmds, child->i);
	setup_input(child, cmd);
	setup_output(child, cmd);
	close(child->infile_fd);
	close_pipes(child->pipes, child->cmd_count - 1);
	exec_cmd(cmd->args, find_env_paths(child->env), mini, child);
}
