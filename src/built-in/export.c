/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:47:38 by obajja            #+#    #+#             */
/*   Updated: 2025/07/11 21:48:51 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_and_free(char **export_list)
{
	int	i;

	i = -1;
	if (export_list)
	{
		while (export_list[++i])
			printf("%s\n", export_list[i]);
		ft_freestrs(export_list);
		export_list = NULL;
	}
}

char	**ft_export_expand(char **env_sorted)
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
	return (new_env);
}

char	**ft_env_sort(char **export_list)
{
	char	**env_export;
	char	*s;	
	int		i;	
	int		f;

	f = -1;
	env_export = ft_strsndup(export_list, ft_strslen(export_list));
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
	ft_freestrs(export_list);
	return (env_export);
}

void	add_to_exp(t_mini *mini, char *arg, int result)
{
	char	**new_env;
	char	**new_exp;

	if (result == EXPORT_ADD_EXPORT || result == EXPORT_ADD_BOTH)
	{
		new_exp = ft_strsjoin(mini->exp_dup, arg);
		ft_freestrs(mini->exp_dup);
		mini->exp_dup = new_exp;
	}
	if (result == EXPORT_ADD_ENV || result == EXPORT_ADD_BOTH)
	{
		new_env = ft_strsjoin(mini->env, arg);
		ft_freestrs(mini->env);
		mini->env = new_env;
	}
}

int	ft_export(t_mini *mini, char **command)
{
	int		result;
	int		i;

	i = 0;
	if (!mini->exp_dup)
		mini->exp_dup = ft_strsndup(mini->env, ft_strslen(mini->env));
	if (!command[1])
		export_printer(mini);
	while (command[++i])
	{
		if (ft_export_checker(command[i]) == 1)
			return (1);
		result = is_to_add_replace(mini->exp_dup, command[i]);
		if (result == EXPORT_ADD_BOTH || result == EXPORT_ADD_EXPORT)
		{
			add_to_exp(mini, command[i], result);
		}
		else if (result == EXPORT_REPLACE)
			replace_to_exp(mini, command[i], -1);
	}
	return (0);
}
