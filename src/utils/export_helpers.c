/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:25:10 by obajja            #+#    #+#             */
/*   Updated: 2025/07/10 17:22:31 by obajja           ###   ########.fr       */
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

int	ft_export_checker(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '=' || ft_isdigit(str[0]))
	{
		ft_putstr_fd(" not a valid identifier\n", 2);
		return (1);
	}
	while (str[++i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '=')
		{
			ft_putstr_fd(" not a valid identifier\n", 2);
			return (1);
		}
	}
	return (0);
}
