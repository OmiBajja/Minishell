/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:25:10 by obajja            #+#    #+#             */
/*   Updated: 2025/07/14 15:54:13 by obajja           ###   ########.fr       */
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

int	replace_to_exp(t_mini *mini, char *to_replace, int equals_index)
{
	char	*variable_name;

	while (to_replace[++equals_index] != '=')
		;
	variable_name = ft_strndup(to_replace, equals_index);
	if (!is_it_in_env(mini->env, variable_name))
	{
		if (env_replacer(mini, to_replace, equals_index))
			return (EXIT_FAILURE);
	}
	else
		if (add_to_exp(mini, to_replace, EXPORT_ADD_ENV))
			return (free(variable_name), EXIT_FAILURE);
	free(variable_name);
	if (export_replacer(mini, to_replace, equals_index))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	is_to_add_replace(char **env, char *word)
{
	int	equals_index;
	int	i;

	i = -1;
	equals_index = -1;
	if (!word || !env)
		return (EXIT_FAILURE);
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
		return (EXIT_FAILURE);
	}
	while (str[++i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '=')
		{
			ft_printf_fd(2,
				"minishell: export: '%s': not a valid identifier\n", str);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
