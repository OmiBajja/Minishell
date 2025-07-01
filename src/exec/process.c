/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:24:19 by pafranci          #+#    #+#             */
/*   Updated: 2025/07/01 19:16:22 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pipex(char *infile, t_parsing *cmds, int cmd_count, char **env, t_mini *mini)
{
	t_child				*child;
	struct sigaction	default_action;

	child = ft_calloc(1, sizeof(t_child));
	if (!infile)
		perror_exit();
	child->infile_fd = open(infile, O_RDONLY);
	if (child->infile_fd < 0)
		perror_exit();
	child->cmds = cmds;
	child->cmd_count = cmd_count;
	child->env = env;
	child->pipes = create_pipes(cmd_count - 1);
	child->pid = ft_calloc(sizeof(pid_t), cmd_count);
	if (!child->pid)
		perror_exit();
	sigemptyset(&default_action.sa_mask);
	default_action.sa_handler = SIG_DFL;
	default_action.sa_flags = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	child->i = -1;
	while (++(child->i) < cmd_count)
	{
		child->pid[child->i] = fork();
		if (child->pid[child->i] < 0)
			perror_exit();
		if (child->pid[child->i] == 0)
			child_process(child, mini);
	}
	close_pipes(child->pipes, cmd_count - 1);
	wait_for_children(child->pid, cmd_count, mini);
	free_pipex(child->infile_fd, child->pipes, cmd_count, child->pid);
	free(child);
	signal_handling();
}

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
	exec_cmd(cmd->args, find_env_paths(child->env), child->env, mini, child);
}
