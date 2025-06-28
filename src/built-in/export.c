/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:47:38 by obajja            #+#    #+#             */
/*   Updated: 2025/06/28 05:54:42 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_and_free(char **env_sorted, char **export_list)
{
	int	i;

	i = -1;
	while (export_list[++i])
		printf("%s\n", export_list[i]);
	if (env_sorted)
	{
		ft_freestrs(env_sorted);
		env_sorted = NULL;
	}
	if (export_list)
	{
		ft_freestrs(export_list);
		export_list = NULL;
	}
}

void	ft_export_expand(char **env_sorted)
{
	char	**new_env;
	int		export_j;
	int		i;
	int		j;

	i = -1;
	new_env = ft_calloc(ft_strslen(env_sorted) + 1, sizeof(char *));
	while (env_sorted[++i])
	{
		j = -1;
		export_j = 6;
		new_env[i] = ft_calloc(ft_strlen(env_sorted[i]) + 10, sizeof(char));
		ft_strlcpy(new_env[i], "export ", 8);
		while (env_sorted[i][++j] && env_sorted[i][j] != '=')
			new_env[i][++export_j] = env_sorted[i][j];
		if (env_sorted[i][j] == '=')
			ft_strlcpy(&new_env[i][++export_j], "=\"", 3);
		export_j += 1;
		while (env_sorted[i][++j])
			new_env[i][++export_j] = env_sorted[i][j];
		new_env[i][++export_j] = '"';
	}
	print_and_free(env_sorted, new_env);
}

void	ft_env_sort(t_mini *mini)
{
	char	**env_export;
	char	*s;	
	int		i;	
	int		f;

	f = -1;
	env_export = ft_strsndup(mini->env, ft_strslen(mini->env));
	while (++f <= ft_strslen(env_export))
	{
		i = -1;
		while (++i < ft_strslen(env_export) - 1)
		{
			if (ft_strcmp(env_export[i], env_export[i + 1]) > 0)
			{
				s = env_export[i];
				env_export[i] = env_export[i + 1];
				env_export[i + 1] = s;
			}
		}
		i = 1;
	}
	i = -1;
	ft_export_expand(env_export);
}

void	ft_export(t_mini *mini, char **command)
{
	char	**new_env;

	new_env = NULL;
	if (command[1])
	{
		new_env = ft_strsjoin(mini->env, command[1]);
		ft_freestrs(mini->env);
		mini->env = new_env;
	}
	else
		ft_env_sort(mini);
}
