/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 05:55:38 by pafranci          #+#    #+#             */
/*   Updated: 2025/07/14 14:13:31 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*ft_get_env_val(char **env, const char *key)
{
	int	i;
	int	key_len;

	if (!env | !key)
		return (NULL);
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
		ft_printf_fd(STDOUT_FILENO, "%s\n", target);
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
		ft_printf_fd(2, "cd: %s: No such file or directory\n", target);
		return (1);
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	if (old_pwd)
	{
		if (ft_replace_env(&mini->env, "OLDPWD", old_pwd))
			return (EXIT_FAILURE);
	}
	if (ft_replace_env(&mini->env, "PWD", cwd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_cd(t_mini *mini, char **args)
{
	char	*target;
	char	*old_pwd;
	int		arg_count;

	arg_count = 0;
	if (!args)
		return (EXIT_FAILURE);
	while (args[arg_count])
		arg_count++;
	if (arg_count > 2)
	{
		ft_printf_fd(2, "cd: too many arguments\n");
		return (EXIT_FAILURE);
	}
	target = ft_cd_get_target(mini, args);
	if (!target)
	{
		if (args[1])
			ft_printf_fd(2, "cd: %s not set\n", "OLDPWD");
		else
			ft_printf_fd(2, "cd: %s not set\n", "HOME");
		return (EXIT_FAILURE);
	}
	old_pwd = ft_get_env_val(mini->env, "PWD");
	return (ft_cd_do(mini, target, old_pwd));
}
