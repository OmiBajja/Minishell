/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:54:01 by obajja            #+#    #+#             */
/*   Updated: 2025/07/13 13:11:34 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_it_in_env(char **exp_list, char *to_find)
{
	int		i;

	i = -1;
	if (!exp_list | !to_find)
		return (EXIT_FAILURE);
	while (exp_list[++i])
	{
		if (ft_strncmp(exp_list[i], to_find, ft_strlen(to_find)) == 0)
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

char	**ft_cut_env(char **list, char *command, char **copy)
{
	size_t	i;
	int		j;

	i = -1;
	j = -1;
	if (!list)
		return (NULL);
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
	env_cpy = ft_cut_env(env, command, env_cpy);
	return (env_cpy);
}

int	ft_unset(t_mini *mini, char **command)
{
	int		i;

	i = 0;
	if (!command[i + 1])
		return (EXIT_SUCCESS);
	if (!mini->exp_dup)
		mini->exp_dup = ft_strsndup(mini->env, ft_strslen(mini->env));
	if (!mini->exp_dup)
		return (EXIT_FAILURE);
	while (command[++i])
	{
		if (is_it_in_env(mini->exp_dup, command[i]))
			return (EXIT_SUCCESS);
		mini->exp_dup = ft_cut_prep(mini->exp_dup, command[i]);
		if (!mini->exp_dup)
			return (EXIT_FAILURE);
		mini->env = ft_cut_prep(mini->env, command[i]);
		if (!mini->env)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
