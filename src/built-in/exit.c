/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:47:31 by obajja            #+#    #+#             */
/*   Updated: 2025/06/23 20:30:25 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void ft_exit(t_mini *mini)
{
    if (mini->env)
        ft_freestrs(mini->env);
    if (mini)
	{
        free(mini);
	}
	printf("exit\n");
	exit(EXIT_SUCCESS);
}