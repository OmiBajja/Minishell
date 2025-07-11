/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:53:35 by pafranci          #+#    #+#             */
/*   Updated: 2025/07/11 23:01:17 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	is_builtin(const char *cmd)
{
	return (!ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "unset"));
}

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
		mini->status = ft_pwd(mini->env);
}

static void	exec_single_builtin(t_parsing *head, t_mini *mini)
{
	int	saved_in;
	int	saved_out;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (setup_redirs_list(head->redirs) != 0)
	{
		mini->status = 1;
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in);
		close(saved_out);
		return ;
	}
	exec_builtin(head, mini);
	fflush(stdout);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
}

static void	no_cmd_redir(t_parsing *head, t_mini *mini)
{
	int	saved_in;
	int	saved_out;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (setup_redirs_list(head->redirs) < 0)
		mini->status = 1;
	else
		mini->status = 0;
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
}

void	exec_handler(t_parsing *head, char **envp, t_mini *mini)
{
	t_pipex	p;

	if (head && head->cmd == NULL && head->redirs)
	{
		no_cmd_redir(head, mini);
		return ;
	}
	if (head && head->next == NULL && is_builtin(head->cmd))
	{
		exec_single_builtin(head, mini);
		return ;
	}
	p.infile = prep_heredoc_get_infile(head, &p.cmd_count, mini);
	p.cmds = head;
	p.env = envp;
	p.mini = mini;
	pipex(&p);
	cleanup_heredoc(head);
}
