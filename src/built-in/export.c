/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:47:38 by obajja            #+#    #+#             */
/*   Updated: 2025/06/13 20:22:13 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void ft_export(t_mini *mini, char *command)
{
    char **new_env;
    
    new_env = ft_strsjoin (mini->env, command);
    ft_freestrs(mini->env);
    mini->env = new_env;
}
