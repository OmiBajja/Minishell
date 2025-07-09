/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:16:30 by pafranci          #+#    #+#             */
/*   Updated: 2025/07/08 15:37:01 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_redir	*new_redir(int type, char *file)
{
	t_redir	*r;

	r = ft_calloc(sizeof(t_redir), 1);
	if (!r)
		return (NULL);
	r->type = type;
	r->file = ft_strdup(file);
	return (r);
}

void	append_redir(t_parsing *cmd, int type, char *file)
{
	t_redir	*r;
	t_redir	*iter;

	r = new_redir(type, file);
	if (!r)
		return ;
	if (!cmd->redirs)
		cmd->redirs = r;
	else
	{
		iter = cmd->redirs;
		while (iter->next)
			iter = iter->next;
		iter->next = r;
	}
}
