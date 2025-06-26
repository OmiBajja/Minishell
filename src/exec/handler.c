/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:53:35 by pafranci          #+#    #+#             */
/*   Updated: 2025/06/25 20:39:47 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool is_builtin(const char *cmd)
{
	return (!strcmp(cmd, "cd")
		|| !strcmp(cmd, "echo")
		|| !strcmp(cmd, "env")
		|| !strcmp(cmd, "exit")
		|| !strcmp(cmd, "export")
		|| !strcmp(cmd, "pwd")
		|| !strcmp(cmd, "unset"));
}

static void exec_builtin(t_parsing *node, t_mini *mini)
{
	if (!strcmp(node->cmd, "cd"))
		ft_cd(mini, node->args);
	else if (!strcmp(node->cmd, "export"))
		ft_export(mini, node->args[1]);
	else if (!strcmp(node->cmd, "unset"))
		ft_unset(mini, node->args[1]);
	else if (!strcmp(node->cmd, "echo"))
		ft_echo(&node->args[1]);
	else if (!strcmp(node->cmd, "env"))
		ft_env(mini->env);
	else if (!strcmp(node->cmd, "exit"))
		ft_exit(mini);
	else if (!strcmp(node->cmd, "pwd"))
		ft_pwd(mini->env);
}

char	*handle_heredoc(const char *delim)
{
	char	*line;
	int		fd;
	char	*filename;

	filename = ft_strdup("/tmp/.minishell_heredoc");
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
	{
		perror("heredoc");
		return (NULL);
	}
	while (42)
	{
		line = readline("> ");
		if (!line || !strcmp(line, delim))
		{
			free(line);
			break;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (filename);
}

void	exec_handler(t_parsing *head, char **envp, t_mini *mini)
{
	int		saved_in;
	int		saved_out;
	int		fd;
	t_parsing *node;
	int		cmd_count;
	char	*infile;

	// Builtin short-circuit (single builtin with redirection)
	if (head->next == NULL && is_builtin(head->cmd))
	{
		saved_in = dup(STDIN_FILENO);
		saved_out = dup(STDOUT_FILENO);

		if (head->infile)
		{
			fd = open(head->infile, O_RDONLY);
			if (fd >= 0)
			{
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
		}
		if (head->append_outfile || head->outfile)
		{
			if (head->append_outfile)
				fd = open(head->append_outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
			else
				fd = open(head->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd >= 0)
			{
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
		}
		exec_builtin(head, mini);
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in);
		close(saved_out);
		return;
	}

	// Count number of commands (t_parsing nodes)
	cmd_count = 0;
	node = head;
	infile = NULL;
	while (node)
	{
		cmd_count++;
		if (node->heredoc_delim)
			node->heredoc_file = handle_heredoc(node->heredoc_delim);
		if (node->infile && !infile && !node->heredoc_file)
			infile = node->infile;
		node = node->next;
	}
	if (!infile)
		infile = "/dev/stdin";

	// Execute via pipex with per-node handling
	pipex(infile, head, cmd_count, envp);
	node = head;
	while (node)
	{
		if (node->heredoc_file)
			unlink(node->heredoc_file);
		node = node->next;
	}
}

/*void	exec_handler(t_parsing *head, char **envp, t_mini *mini)
{
	int	saved_in;
	int	saved_out;
	int	fd;

	if (head->next == NULL && is_builtin(head->cmd))
	{
		saved_in = dup(STDIN_FILENO);
		saved_out = dup(STDOUT_FILENO);

		if (head->infile)
		{
			fd = open(head->infile, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		if (head->outfile || head->append_outfile)
		{
			if (head->append_outfile)
				fd = open(head->append_outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
			else
				fd = open(head->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		exec_builtin(head, mini);
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in);
		close(saved_out);
		return ;
	}

	t_parsing	*node;
	char		**cmds;
	char		*infile;
	char		*outfile;
	char		*append_outfile;
	int			cmd_count;
	int			i;
	int			j;
	int			len;

	cmd_count = 0;
	node = head;
	infile = NULL;
	outfile = NULL;
	append_outfile = NULL;
	while (node)
	{
		cmd_count++;
		if (node->infile && !infile)
			infile = node->infile;
		if (node->outfile)
			outfile = node->outfile;
		if (node->append_outfile)
			append_outfile = node->append_outfile;
		node = node->next;
	}
	if (!infile)
		infile = "/dev/stdin";
	if (!outfile && !append_outfile)
		outfile = "/dev/stdout";
	cmds = malloc((cmd_count + 1) * sizeof(char *));
	if (!cmds)
	{
		perror("malloc");
		return ;
	}
	node = head;
	i = 0;
	while (node)
	{
		j = 0;
		len = 0;
		while (node->args[j])
		{
			len += ft_strlen(node->args[j]) + 1;
			j++;
		}
		cmds[i] = malloc(len + 1);
		if (!cmds[i])
		{
			perror("malloc");
			exit(1);
		}
		cmds[i][0] = '\0';
		j = 0;
		while (node->args[j])
		{
			strcat(cmds[i], node->args[j]);
			if (node->args[j + 1])
				strcat(cmds[i], " ");
			j++;
		}
		i++;
		node = node->next;
	}
	cmds[i] = NULL;
	pipex(infile, outfile, append_outfile, cmds, cmd_count, envp);
	i = 0;
	while (i < cmd_count)
	{
		free(cmds[i]);
		i++;
	}
	free(cmds);
}*/
