/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:47:24 by obajja            #+#    #+#             */
/*   Updated: 2025/07/09 18:04:44 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_env(char **envp)
{
	int	i;

	i = -1;
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

void	ft_replace_env(char ***envp, const char *key, const char *value)
{
	char	*new_pwd;
	char	**new_env;
	char	*temp;

	new_pwd = ft_strjoin(key, "=");
	temp = new_pwd;
	new_pwd = ft_strjoin(new_pwd, value);
	free(temp);
	temp = NULL;
	if (!try_replace(*envp, key, new_pwd))
	{
		new_env = ft_strsjoin(*envp, new_pwd);
		ft_freestrs(*envp);
		*envp = new_env;
		free(new_pwd);
	}
}
