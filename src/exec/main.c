/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:48:41 by pafranci          #+#    #+#             */
/*   Updated: 2025/05/29 02:18:29 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

/*int	forks_and_pipes(t_env_data env_data, char *av[])
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (pipe(fd) == -1)
		perror_exit();
	pid1 = fork();
	if (pid1 < 0)
		perror_exit();
	else if (pid1 == 0)
		child1(fd, av[1], av[2], env_data);
	pid2 = fork();
	if (pid2 < 0)
		perror_exit();
	else if (pid2 == 0)
		child2(fd, av[4], av[3], env_data);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	main(int ac, char *av[], char **env)
{
//	t_env_data	env_data;
	char		*infile;
	char		*outfile;
	int			cmd_count;
	char		**cmds;

	if (ac < 5)
		invalid_usage_exit(ac);
	infile = av[1];
	outfile = av[ac - 1];
	cmd_count = ac - 3;
	cmds = &av[2];
	env_data.env = env;
	env_data.paths = find_env_paths(env);
	if (!env_data.paths)
		perror_exit();
	return (forks_and_pipes(env_data, av));

	pipex(infile, outfile, cmds, cmd_count, env);
	return (0);
}
*/