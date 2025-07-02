/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:48:20 by pafranci          #+#    #+#             */
/*   Updated: 2025/07/03 00:00:15 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*find_cmd_in_pahts(const char *cmd, char **env_paths_tab)
{
	char	*cmd_path;
	char	*full_cmd;
	int		i;

	i = -1;
	while (env_paths_tab[++i])
	{
		cmd_path = ft_strjoin(env_paths_tab[i], "/");
		full_cmd = ft_strjoin(cmd_path, cmd);
		free(cmd_path);
		if (!full_cmd)
			return (NULL);
		if (access(full_cmd, F_OK | X_OK) == 0)
			return (full_cmd);
		free(full_cmd);
	}
	return (NULL);
}

static char	*get_full_cmd(char **cmd_tab, const char *paths, t_mini *mini,
		t_child *child)
{
	char	*full_cmd;
	char	**env_paths_tab;

	if (ft_strstr(cmd_tab[0], "/"))
	{
		if (access(cmd_tab[0], F_OK | X_OK) == 0)
			return (cmd_tab[0]);
		command_not_found_exit(cmd_tab, mini, child);
	}
	env_paths_tab = ft_split_pau(paths, ':');
	if (!env_paths_tab)
		return (NULL);
	full_cmd = find_cmd_in_pahts(cmd_tab[0], env_paths_tab);
	free_tab(env_paths_tab);
	if (full_cmd)
		return (full_cmd);
	return (command_not_found_exit(cmd_tab, mini, child), NULL);
}

void	exec_cmd(char **cmd_args, char const *paths, t_mini *mini,
		t_child *child)
{
	char	*full_cmd;

	if (!cmd_args || !cmd_args[0])
	{
		write(2, "'': command not found\n", 22);
		exit(127);
	}
	full_cmd = get_full_cmd(cmd_args, paths, mini, child);
	if (!full_cmd)
		perror_exit();
	if (execve(full_cmd, cmd_args, mini->env) == -1)
	{
		free(full_cmd);
		perror_exit();
	}
}
