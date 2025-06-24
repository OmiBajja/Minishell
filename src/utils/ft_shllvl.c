/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shllvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:53:05 by obajja            #+#    #+#             */
/*   Updated: 2025/06/24 15:04:19 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void ft_shllvl(t_mini  *mini)
{
    int j;

    j = -1;
    while (mini->env[++j])
	{
        if (ft_strncmp(mini->env[j],"SHLVL", ft_strlen("SHLVL")) == 0)
            mini->env[j][6] += 1;
    }
}
