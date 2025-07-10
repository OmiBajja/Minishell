/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 05:55:38 by pafranci          #+#    #+#             */
/*   Updated: 2025/07/09 19:01:24 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*ft_get_env_val(char **env, const char *key)
{
	int	i;
	int	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (&env[i][key_len + 1]);
		i++;
	}
	return (NULL);
}

static char	*ft_cd_get_target(t_mini *mini, char **args)
{
	char	*target;

	if (!args || !args[0])
		return (NULL);
	if (!args[1])
	{
		target = ft_get_env_val(mini->env, "HOME");
		if (!target)
			return (NULL);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		target = ft_get_env_val(mini->env, "OLDPWD");
		if (!target)
			return (NULL);
		printf("%s\n", target);
	}
	else
		target = args[1];
	return (target);
}

static int	ft_cd_do(t_mini *mini, const char *target, const char *old_pwd)
{
	char	cwd[1024];

	if (chdir(target) != 0)
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		return (1);
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("cd");
		return (1);
	}
	if (old_pwd)
		ft_replace_env(&mini->env, "OLDPWD", old_pwd);
	ft_replace_env(&mini->env, "PWD", cwd);
	return (0);
}

int	ft_cd(t_mini *mini, char **args)
{
	char	*target;
	char	*old_pwd;

	if (args[2])
	{
		ft_putstr_fd(" too many arguments\n", 2);
		return (1);
	}
	target = ft_cd_get_target(mini, args);
	if (!target)
	{
		if (args[1])
			printf("cd: %s not set\n", "OLDPWD");
		else
			printf("cd: %s not set\n", "HOME");
		return (1);
	}
	old_pwd = ft_get_env_val(mini->env, "PWD");
	return (ft_cd_do(mini, target, old_pwd));
}
