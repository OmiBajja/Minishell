/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cleaner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:10:12 by obajja            #+#    #+#             */
/*   Updated: 2025/06/30 19:08:06 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	mini_cleaner(t_mini *mini)
{
	if (mini->env)
	{
		ft_freestrs(mini->env);
		mini->env = NULL;
	}
	if (mini->exp_dup)
	{
		ft_freestrs(mini->exp_dup);
		mini->exp_dup = NULL;
	}
	if (mini->data)
		free_parse(mini->data);
	if (mini->lex)
		free_tokens(mini->lex);
	if (mini)
	{
		free(mini);
		mini = NULL;
	}
}
