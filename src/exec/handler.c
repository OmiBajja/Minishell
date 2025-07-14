/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:53:35 by pafranci          #+#    #+#             */
/*   Updated: 2025/07/14 16:44:03 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	exec_builtin(t_parsing *node, t_mini *mini)
{
	if (!node->cmd)
		return ;
	if (!ft_strcmp(node->cmd, "cd"))
		mini->status = ft_cd(mini, node->args);
	else if (!ft_strcmp(node->cmd, "export"))
		mini->status = ft_export(mini, node->args);
	else if (!ft_strcmp(node->cmd, "unset"))
		mini->status = ft_unset(mini, node->args);
	else if (!ft_strcmp(node->cmd, "echo"))
		mini->status = ft_echo(node->args);
	else if (!ft_strcmp(node->cmd, "env"))
		mini->status = ft_env(mini->env);
	else if (!ft_strcmp(node->cmd, "exit"))
		mini->status = ft_exit(mini, node->args);
	else if (!ft_strcmp(node->cmd, "pwd"))
		mini->status = ft_pwd();
}

static void	exec_single_builtin(t_parsing *head, t_mini *mini)
{
	mini->saved_in = dup(STDIN_FILENO);
	mini->saved_out = dup(STDOUT_FILENO);
	if (setup_redirs_list(head->redirs, NULL, mini) != 0)
	{
		mini->status = 1;
		dup2(mini->saved_in, STDIN_FILENO);
		dup2(mini->saved_out, STDOUT_FILENO);
		close(mini->saved_in);
		close(mini->saved_out);
		return ;
	}
	exec_builtin(head, mini);
	dup2(mini->saved_in, STDIN_FILENO);
	dup2(mini->saved_out, STDOUT_FILENO);
	close(mini->saved_in);
	close(mini->saved_out);
}

static void	no_cmd_redir(t_parsing *head, t_mini *mini)
{
	mini->saved_in = dup(STDIN_FILENO);
	mini->saved_out = dup(STDOUT_FILENO);
	if (setup_redirs_list(head->redirs, NULL, mini) < 0)
		mini->status = 1;
	else
		mini->status = 0;
	dup2(mini->saved_in, STDIN_FILENO);
	dup2(mini->saved_out, STDOUT_FILENO);
	close(mini->saved_in);
	close(mini->saved_out);
}

static void	setup_p(t_pipex *p, t_parsing *head, char **envp, t_mini *mini)
{
	p->infile = prep_heredoc_get_infile(head, &p->cmd_count, mini);
	if (!p->infile && g_sig == 130)
	{
		mini->status = 128 + SIGINT;
		g_sig = 0;
		return ;
	}
	p->cmds = head;
	p->env = envp;
	p->mini = mini;
	pipex(p);
	cleanup_heredoc(head);
}

void	exec_handler(t_parsing *head, char **envp, t_mini *mini)
{
	t_pipex	p;
	int		i;
	char	*tmp;

	if (head && head->cmd == NULL && head->redirs)
	{
		tmp = prep_heredoc_get_infile(head, &i, mini);
		if (!tmp && g_sig == SIGINT)
		{
			mini->status = 128 + SIGINT;
			g_sig = 0;
			return ;
		}
		no_cmd_redir(head, mini);
		cleanup_heredoc(head);
		return ;
	}
	if (head && head->next == NULL && is_builtin(head->cmd))
	{
		exec_single_builtin(head, mini);
		return ;
	}
	setup_p(&p, head, envp, mini);
	
}
