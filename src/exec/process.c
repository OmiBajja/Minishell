/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:24:19 by pafranci          #+#    #+#             */
/*   Updated: 2025/06/26 18:27:07 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void pipex(char *infile, t_parsing *cmds, int cmd_count, char **env)
{
	int		infile_fd;
	int		**pipes;
	int		i;
	pid_t	*pid;

	infile_fd = open(infile, O_RDONLY);
	if (infile_fd < 0)
		perror_exit();

	pipes = create_pipes(cmd_count - 1);
	pid = malloc(sizeof(pid_t) * cmd_count);
	if (!pid)
		perror_exit();

	for (i = 0; i < cmd_count; i++)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			perror_exit();
		if (pid[i] == 0)
			child_process(i, infile_fd, cmds, env, pipes, cmd_count);
	}

	for (i = 0; i < cmd_count; i++)
		waitpid(pid[i], NULL, 0);

	close(infile_fd);
	close_pipes(pipes, cmd_count - 1);
	for (i = 0; i < cmd_count - 1; i++)
		free(pipes[i]);
	free(pipes);
	free(pid);
}

/*void pipex(char *infile, char *outfile, char *append_outfile, char **cmds, int cmd_count, char **env)
{
	int		infile_fd;
	int		outfile_fd;
	int		**pipes;
	int		i;
	pid_t	*pid;

	infile_fd = open(infile, O_RDONLY);
	if (infile_fd < 0)
		perror_exit();
	if (append_outfile)
		outfile_fd = open(append_outfile, O_CREAT | O_WRONLY | O_APPEND);
	else
		outfile_fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (outfile_fd < 0)
		perror_exit();
	pipes = create_pipes(cmd_count - 1);
	i = 0;
	pid = malloc(sizeof(pid_t *));
	while (i < cmd_count)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			perror_exit();
		if (pid[i] == 0)
			child_process(i, infile_fd, outfile_fd, cmds[i], env, pipes, cmd_count);
		i++;
	}
	i = 0;
	while (i < cmd_count)
		waitpid(pid[i++], NULL, 0);
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
}*/


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

void child_process(int index, int infile_fd, t_parsing *cmds, char **env, int **pipes, int cmd_count)
{
	t_parsing	*cmd;
	int			fd;

	fd = -1;
	cmd = get_nth_node(cmds, index);
	if (cmd->heredoc_file)
	{
		fd = open(cmd->heredoc_file, O_RDONLY);
		if (fd < 0)
			perror_exit();
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (index == 0)
		dup2(infile_fd, STDIN_FILENO);
	else
		dup2(pipes[index - 1][0], STDIN_FILENO);
	if (index == cmd_count - 1)
	{
		if (cmd->append_outfile)
			fd = open(cmd->append_outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (cmd->outfile)
			fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd >= 0)
		{
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
	}
	close(infile_fd);
	close_pipes(pipes, cmd_count - 1);
	exec_cmd(cmd->cmd, find_env_paths(env), env);
}
