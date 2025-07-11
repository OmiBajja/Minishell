/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cleaner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:10:12 by obajja            #+#    #+#             */
/*   Updated: 2025/07/11 23:41:17 by obajja           ###   ########.fr       */
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
	if (mini)
	{
		free(mini);
		mini = NULL;
	}
}

void	free_tokens(t_lex *tokens)
{
	t_lex	*tmp;

	while (tokens != NULL)
	{
		tmp = tokens->next;
		if (tokens->value)
			free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}

void	master_cleaner(t_mini *mini, t_child *child)
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
