/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shllvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:53:05 by obajja            #+#    #+#             */
/*   Updated: 2025/07/15 16:20:33 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static	void	shl_not_set(t_mini *mini, int i, int err)
{
	char	**env_temp;

	if (err == 1)
	{
		if (mini->env[i])
			free(mini->env[i]);
		mini->env[i] = ft_strdup("SHLVL=0");
		if (!mini->env[i])
			return (ft_freestrs(mini->env));
	}
	else
	{
		env_temp = ft_strsjoin(mini->env, "SHLVL=0");
		if (!env_temp)
			return ;
		free(mini->env);
		mini->env = env_temp;
	}
}

static	void	true_shlvl(t_mini *mini, int i)
{
	int		shllvl_num;
	char	*shllvl_string;
	char	*result;

	shllvl_num = ft_atoi(&mini->env[i][6]);
	if (shllvl_num < 999)
		shllvl_num += 1;
	shllvl_string = ft_itoa(shllvl_num);
	result = ft_strjoin("SHLVL=", shllvl_string);
	free(shllvl_string);
	free(mini->env[i]);
	mini->env[i] = result;
}

void	ft_shllvl(t_mini *mini)
{
	int	j;
	int	i;
	int	err;

	i = -1;
	j = 5;
	err = 0;
	while (mini->env[++i] && err == 0)
	{
		if (ft_strncmp(mini->env[i], "SHLVL=", ft_strlen("SHLVL=")) == 0)
		{
			while (mini->env[i][++j] && err == 0)
			{
				if (!ft_isdigit(mini->env[i][j]))
					err = 1;
			}
			if (err != 1)
				true_shlvl(mini, i);
			break ;
		}
	}
	if (!mini->env[i] || err == 1)
		shl_not_set(mini, i, err);
}
