/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:54:01 by obajja            #+#    #+#             */
/*   Updated: 2025/07/12 00:41:53 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_it_in_env(char **exp_list, char *to_find)
{
	int		i;

	i = -1;
	while (exp_list[++i])
	{
		if (ft_strncmp(exp_list[i], to_find, ft_strlen(to_find)) == 0)
			return (1);
	}
	return (0);
}

char	**ft_cut_env(char **list, char *command, char **copy)
{
	size_t	i;
	int		j;

	i = -1;
	j = -1;
	while (list[++j])
	{
		if (ft_strncmp(list[j], command, ft_strlen(command)) == 0)
			continue ;
		else
		{
			copy[++i] = ft_strdup(list[j]);
			if (!copy[i])
			{
				ft_freestrs(copy);
				return (NULL);
			}
		}
	}
	ft_freestrs(list);
	return (copy);
}

char	**ft_cut_prep(char **env, char *command)
{
	int		size;
	char	**env_cpy;

	size = ft_strslen(env);
	env_cpy = ft_calloc((size + 1), sizeof(char *));
	if (!env_cpy)
		return (NULL);
	return (ft_cut_env(env, command, env_cpy));
}

int	ft_unset(t_mini *mini, char **command)
{
	int		i;

	i = 0;
	if (!command[i + 1])
		return (0);
	if (!mini->exp_dup)
		mini->exp_dup = ft_strsndup(mini->env, ft_strslen(mini->env));
	while (command[++i])
	{
		if (!is_it_in_env(mini->exp_dup, command[i]))
			return (0);
		mini->exp_dup = ft_cut_prep(mini->exp_dup, command[i]);
		if (!mini->exp_dup)
			return (1);
		mini->env = ft_cut_prep(mini->env, command[i]);
		if (!mini->env)
			return (1);
	}
	return (0);
}
