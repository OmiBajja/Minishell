/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:16:14 by obajja            #+#    #+#             */
/*   Updated: 2025/07/14 13:27:08 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	export_replacer(t_mini *mini, char *to_replace, int equals_index)
{
	int	i;

	i = -1;
	while (mini->exp_dup[++i])
	{
		if (!ft_strncmp(mini->exp_dup[i], to_replace, equals_index))
		{
			free(mini->exp_dup[i]);
			mini->exp_dup[i] = ft_strdup(to_replace);
			if (!mini->exp_dup[i])
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	env_replacer(t_mini *mini, char *to_replace, int equals_index)
{
	int	i;

	i = -1;
	while (mini->env[++i])
	{
		if (!ft_strncmp(mini->env[i], to_replace, equals_index))
		{
			free(mini->env[i]);
			mini->env[i] = ft_strdup(to_replace);
			if (!mini->env[i])
				return (ft_freestrs(mini->env), EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

char	*exporter_expander(char *new_env, char *env_sorted)
{
	int	j;
	int	export_j;

	j = -1;
	export_j = 6;
	ft_strlcpy(new_env, "export ", 8);
	while (env_sorted[++j] && env_sorted[j] != '=')
		new_env[++export_j] = env_sorted[j];
	if (env_sorted[j] == '=')
		ft_strlcpy(&new_env[++export_j], "=\"", 3);
	export_j += 1;
	while (env_sorted[++j])
		new_env[++export_j] = env_sorted[j];
	new_env[++export_j] = '"';
	return (new_env);
}
