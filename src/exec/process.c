/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:24:19 by pafranci          #+#    #+#             */
/*   Updated: 2025/07/01 12:08:43 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pipex(char *infile, t_parsing *cmds, int cmd_count, char **env, t_mini *mini)
{
	pid_t				*pid;
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
	pid = malloc(sizeof(pid_t) * cmd_count);
	if (!pid)
		perror_exit();
	sigemptyset(&default_action.sa_mask);
	default_action.sa_handler = SIG_DFL;
	default_action.sa_flags = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	child->i = -1;
	while (++(child->i) < cmd_count)
	{
		pid[child->i] = fork();
		if (pid[child->i] < 0)
			perror_exit();
		if (pid[child->i] == 0)
			child_process(child);
	}
	close_pipes(child->pipes, cmd_count - 1);
	wait_for_children(pid, cmd_count, mini);
	free_pipex(child->infile_fd, child->pipes, cmd_count, pid);
	free(child);
	signal_handling();
}

int	**create_pipes(int n)
{
	int	**pipes;
	int	i;

	pipes = malloc(n * sizeof (int *));
	if (!pipes)
		return (perror_exit(), NULL);
	i = 0;
	while (i < n)
	{
		pipes[i] = malloc(2 * sizeof (int));
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

void	child_process(t_child *child)
{
	t_parsing	*cmd;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	cmd = get_nth_node(child->cmds, child->i);
	setup_input(child, cmd);
	setup_output(child, cmd);
	close(child->infile_fd);
	close_pipes(child->pipes, child->cmd_count - 1);
	exec_cmd(cmd->args, find_env_paths(child->env), child->env);
}
