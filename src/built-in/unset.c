/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:54:01 by obajja            #+#    #+#             */
/*   Updated: 2025/06/28 06:02:53 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_unset(t_mini *mini, char *command)
{
	size_t	i;
	int		j;
	int		size;
	char	**env_cpy;

	i = -1;
	j = -1;
	size = ft_strslen(mini->env);
	env_cpy = ft_calloc((size), sizeof(char *));
	// if (!command)
	// 	return (NULL);
	while (mini->env[++j])
	{
		if (ft_strncmp(mini->env[j], command, ft_strlen(command)) == 0)
			continue ;
		else
		{
			env_cpy[++i] = ft_strdup(mini->env[j]);
			if (!env_cpy[i])
				ft_freestrs(env_cpy);
		}
	}
	ft_freestrs(mini->env);
	mini->env = env_cpy;
}
