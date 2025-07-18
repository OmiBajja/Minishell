/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:47:24 by obajja            #+#    #+#             */
/*   Updated: 2025/07/15 17:21:32 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	env_size_checker(t_mini *mini, char *cmd)
{
	int	i;
	int	size;

	i = -1;
	if (!mini->env)
		return (1);
	while (mini->env[++i])
	{
		size = ft_strlen(mini->env[i]);
		if (size > 130000)
		{
			ft_printf_fd(2, "Minishell: %s: Argument list too long\n", cmd);
			return (1);
		}
	}
	return (0);
}

int	ft_env(char **envp)
{
	int	i;

	i = -1;
	if (!envp)
		return (EXIT_FAILURE);
	while (envp[++i])
		printf("%s\n", envp[i]);
	return (0);
}

static bool	try_replace(char **env, const char *key, char *new_pwd)
{
	size_t	key_len;
	int		i;

	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0
			&& env[i][key_len] == '=')
		{
			free(env[i]);
			env[i] = new_pwd;
			return (true);
		}
		i++;
	}
	return (false);
}

int	ft_replace_env(char ***envp, const char *key, const char *value)
{
	char	*new_pwd;
	char	**new_env;
	char	*temp;

	new_pwd = ft_strjoin(key, "=");
	if (!new_pwd)
		return (EXIT_FAILURE);
	temp = new_pwd;
	new_pwd = ft_strjoin(new_pwd, value);
	free(temp);
	temp = NULL;
	if (!new_pwd)
		return (EXIT_FAILURE);
	if (!try_replace(*envp, key, new_pwd))
	{
		new_env = ft_strsjoin(*envp, new_pwd);
		if (!new_env)
			return (ft_freestrs(new_env), free(new_pwd), EXIT_FAILURE);
		ft_freestrs(*envp);
		*envp = new_env;
		free(new_pwd);
	}
	return (EXIT_SUCCESS);
}
