/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:24:19 by pafranci          #+#    #+#             */
/*   Updated: 2025/05/29 02:13:20 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void pipex(char *infile, char *outfile, char **cmds, int cmd_count, char **env)
{
	int		infile_fd;
	int		outfile_fd;
	int		**pipes;
	int		i;
	pid_t	pid;

	infile_fd = open(infile, O_RDONLY);
	if (infile_fd < 0)
		perror_exit();
	outfile_fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (outfile_fd < 0)
		perror_exit();
	pipes = create_pipes(cmd_count - 1);
	i = 0;
	while (i < cmd_count)
	{
		pid = fork();
		if (pid < 0)
			perror_exit();
		if (pid == 0)
			child_process(i, infile_fd, outfile_fd, cmds[i], env, pipes, cmd_count);
		i++;
	}
	close(infile_fd);
	close(outfile_fd);
	close_pipes(pipes, cmd_count - 1);
	i = 0;
	while (i < (cmd_count - 1))
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

int	**create_pipes(int n)
{
	int **pipes;
	int	i;

	pipes = malloc(n * sizeof (int *));
	if (!pipes)
		return(perror_exit(), NULL);
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

void	child_process(int index, int infile_fd, int outfile_fd, char *cmd, char **env, int **pipes, int cmd_count)
{
	if (index == 0)
		dup2(infile_fd, STDIN_FILENO);
	else
		dup2(pipes[index - 1][0], STDIN_FILENO);
	if (index == cmd_count - 1)
		dup2(outfile_fd, STDOUT_FILENO);
	else
		dup2(pipes[index][1], STDOUT_FILENO);
	close(infile_fd);
	close(outfile_fd);
	close_pipes(pipes, cmd_count - 1);
	exec_cmd(cmd, find_env_paths(env), env);
}
