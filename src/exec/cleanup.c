/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:05:48 by obajja            #+#    #+#             */
/*   Updated: 2025/07/10 16:59:42 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	child_cleaner(t_child *child, t_mini *mini)
{
	if (mini->data)
		free_parse(mini->data);
	if (mini->lex)
		free_tokens(mini->lex);
	if (child)
	{
		free_pipex(child->pipes, child->cmd_count, child->pid);
		free(child);
	}
	mini_cleaner(mini);
}
