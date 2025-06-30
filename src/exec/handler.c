/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:53:35 by pafranci          #+#    #+#             */
/*   Updated: 2025/06/30 20:57:08 by obajja           ###   ########.fr       */
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
		ft_cd(mini, node->args);
	else if (!ft_strcmp(node->cmd, "export"))
		ft_export(mini, node->args);
	else if (!ft_strcmp(node->cmd, "unset"))
		ft_unset(mini, node->args[1]);
	else if (!ft_strcmp(node->cmd, "echo"))
		ft_echo(node->args);
	else if (!ft_strcmp(node->cmd, "env"))
		ft_env(mini->env);
	else if (!ft_strcmp(node->cmd, "exit"))
		ft_exit(mini, node->args);
	else if (!ft_strcmp(node->cmd, "pwd"))
		ft_pwd(mini->env);
}

static void	setup_builtin_redirections(t_parsing *node)
{
	int	fd;

	if (node->infile)
	{
		fd = open(node->infile, O_RDONLY);
		if (fd >= 0)
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
	}
	if (node->append_out || node->outfile)
	{
		if (node->append_out)
			fd = open(node->append_out, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(node->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd >= 0)
		{
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
	}
}

static void	exec_single_builtin(t_parsing *head, t_mini *mini)
{
	int	saved_in;
	int	saved_out;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	setup_builtin_redirections(head);
	exec_builtin(head, mini);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
}

void	exec_handler(t_parsing *head, char **envp, t_mini *mini)
{
	int		cmd_count;
	char	*infile;

	if (head->next == NULL && is_builtin(head->cmd))
	{
		exec_single_builtin(head, mini);
		return ;
	}
	infile = prep_heredoc_get_infile(head, &cmd_count);
	pipex(infile, head, cmd_count, envp);
	cleanup_heredoc(head);
}
