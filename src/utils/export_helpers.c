/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:25:10 by obajja            #+#    #+#             */
/*   Updated: 2025/07/09 19:20:30 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_export_checker (char *str)
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
