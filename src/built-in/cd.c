/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 05:55:38 by pafranci          #+#    #+#             */
/*   Updated: 2025/06/28 06:40:57 by pafranci         ###   ########.fr       */
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

static void	ft_replace_env(char ***env, const char *key, const char *value)
{
	int		i;
	char	*new_pwd;
	char	**new_env;
	char	*temp;

	new_pwd = ft_strjoin(key, "=");
	temp = new_pwd;
	new_pwd = ft_strjoin(new_pwd, value);
	free(temp);
	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], key, ft_strlen(key)) == 0 &&
			(*env)[i][ft_strlen(key)] == '=')
		{
			free((*env)[i]);
			(*env)[i] = new_pwd;
			return ;
		}
		i++;
	}
	new_env = ft_strsjoin(*env, new_pwd);
	ft_freestrs(*env);
	*env = new_env;
	free(new_pwd);
}

static char	*ft_cd_get_target(t_mini *mini, char **args)
{
	char	*target;

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
		perror("cd");
		return (0);
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("cd");
		return (0);
	}
	if (old_pwd)
		ft_replace_env(&mini->env, "OLDPWD", old_pwd);
	ft_replace_env(&mini->env, "PWD", cwd);
	return (1);
}

void	ft_cd(t_mini *mini, char **args)
{
	char	*target;
	char	*old_pwd;

	target = ft_cd_get_target(mini, args);
	if (!target)
	{
		if (args[1])
			printf("cd: %s not set\n", "OLDPWD");
		else
			printf("cd: %s not set\n", "HOME");
		return ;
	}
	old_pwd = ft_get_env_val(mini->env, "PWD");
	if (!ft_cd_do(mini, target, old_pwd))
		return ;
}

/*void	ft_cd(t_mini *mini, char **args)
{
	char	*target;
	char	cwd[1024];
	char	*old_pwd;

	if (!args[1])
	{
		target = ft_get_env_val(mini->env, "HOME");
		if (!target)
		{
			printf("cd: HOME not set\n");
			return ;
		}
	}
	else if (strcmp(args[1], "-") == 0)
	{
		target = ft_get_env_val(mini->env, "OLDPWD");
		if (!target)
		{
			printf("cd: OLDPWD not set\n");
			return ;
		}
		printf("%s\n", target);
	}
	else
		target = args[1];
	old_pwd = ft_get_env_val(mini->env, "PWD");
	if (chdir(target) != 0)
	{
		perror ("cd");
		return ;
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("cd");
		return ;
	}
	if (old_pwd)
		ft_replace_env(&mini->env, "OLDPWD", old_pwd);
	ft_replace_env(&mini->env, "PWD", cwd);
}*/