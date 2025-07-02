/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:09:51 by pafranci          #+#    #+#             */
/*   Updated: 2025/07/03 00:03:57 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	setup_pipex(t_pipex *pipex)
{
	pipex->child = ft_calloc(1, sizeof(t_child));
	if (!pipex->infile)
		perror_exit();
	pipex->child->infile_fd = open(pipex->infile, O_RDONLY);
	if (pipex->child->infile_fd < 0)
		perror_exit();
	pipex->child->cmds = pipex->cmds;
	pipex->child->cmd_count = pipex->cmd_count;
	pipex->child->env = pipex->env;
	pipex->child->pipes = create_pipes(pipex->cmd_count - 1);
	pipex->child->pid = ft_calloc(sizeof(pid_t), pipex->cmd_count);
	if (!pipex->child->pid)
		perror_exit();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

static void	fork_children(t_pipex *pipex)
{
	struct sigaction	default_action;

	sigemptyset(&default_action.sa_mask);
	default_action.sa_handler = SIG_DFL;
	default_action.sa_flags = 0;
	pipex->child->i = -1;
	while (++(pipex->child->i) < pipex->cmd_count)
	{
		pipex->child->pid[pipex->child->i] = fork();
		if (pipex->child->pid[pipex->child->i] < 0)
			perror_exit();
		if (pipex->child->pid[pipex->child->i] == 0)
			child_process(pipex->child, pipex->mini);
	}
}

static void	end_pipex(t_pipex *p)
{
	close_pipes(p->child->pipes, p->cmd_count - 1);
	wait_for_children(p->child->pid, p->cmd_count, p->mini);
	free_pipex(p->child->infile_fd, p->child->pipes,
		p->cmd_count, p->child->pid);
	free(p->child);
}

void	pipex(t_pipex *pipex)
{
	setup_pipex(pipex);
	fork_children(pipex);
	end_pipex(pipex);
	signal_handling();
}
