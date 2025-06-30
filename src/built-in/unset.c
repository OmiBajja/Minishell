/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:54:01 by obajja            #+#    #+#             */
/*   Updated: 2025/06/30 18:57:13 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		is_it_in_env(char **exp_list, char *to_find)
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

void	ft_unset(t_mini *mini, char *command)
{
	int		size;
	char	**env_cpy;
	char	**exp_cpy;

	if (!mini->exp_dup)
		mini->exp_dup = ft_strsndup(mini->env, ft_strslen(mini->env));
	if (!is_it_in_env(mini->exp_dup, command))
		return ;
	size = ft_strslen(mini->env);
	env_cpy = ft_calloc((size + 1), sizeof(char *));
	if (!env_cpy)
		return ;
	size = ft_strslen(mini->exp_dup);
	exp_cpy = ft_calloc((size + 1), sizeof(char *));
	if (!exp_cpy)
	{
		ft_freestrs(env_cpy);
		return ;
	}
	mini->exp_dup = ft_cut_env(mini->exp_dup, command, exp_cpy);
	mini->env = ft_cut_env(mini->env, command, env_cpy);
}
