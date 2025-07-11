/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:25:10 by obajja            #+#    #+#             */
/*   Updated: 2025/07/11 18:05:47 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*status_code(t_mini *mini)
{
	char	*replace;

	replace = ft_itoa(mini->status + g_sig);
	g_sig = 0;
	return (replace);
}

void	export_printer(t_mini *mini)
{
	char	**exp_sorted;

	mini->exp_dup = ft_env_sort(mini->exp_dup);
	exp_sorted = ft_export_expand(mini->exp_dup);
	print_and_free(exp_sorted);
}

void	replace_to_exp(t_mini *mini, char *to_replace)
{
	int	equals_index;
	int	i;

	equals_index = -1;
	i = -1;
	while (to_replace[++equals_index] != '=')
		;
	while (mini->env[++i])
	{
		if (!ft_strncmp(mini->env[i], to_replace, equals_index))
		{
			free(mini->env[i]);
			mini->env[i] = ft_strdup(to_replace);
		}
	}
	i = -1;
	while (mini->exp_dup[++i])
	{
		if (!ft_strncmp(mini->exp_dup[i], to_replace, equals_index))
		{
			free(mini->exp_dup[i]);
			mini->exp_dup[i] = ft_strdup(to_replace);
		}
	}
}

int	is_to_add_replace(char **env, char *word)
{
	int	equals_index;
	int	i;

	equals_index = -1;
	i = -1;
	while (word[++equals_index] && word[equals_index] != '=')
		;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], word, equals_index))
		{
			if (word[equals_index] == '=')
				return (EXPORT_REPLACE);
			else
				return (EXPORT_IGNORE);
		}
	}
	if (!ft_strchr(word, '='))
		return (EXPORT_ADD_EXPORT);
	else
		return (EXPORT_ADD_BOTH);
}

int	ft_export_checker(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '=' || ft_isdigit(str[0]))
	{
		ft_printf_fd(2,
			"minishell: export: '%s': not a valid identifier\n", str);
		return (1);
	}
	while (str[++i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '=')
		{
			ft_printf_fd(2,
				"minishell: export: '%s': not a valid identifier\n", str);
			return (1);
		}
	}
	return (0);
}
