/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 09:16:35 by pafranci          #+#    #+#             */
/*   Updated: 2025/07/14 00:16:19 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <readline/history.h>

char	*handle_heredoc(const char *delim, t_mini *mini)
{
	char	*line;
	int		fd;
	char	*filename;
	size_t	len;

	filename = ft_strdup("/tmp/.minishell_heredoc");
	if (!filename)
		return (NULL);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
		return (perror("heredoc"), free(filename), NULL);
	while (42)
	{
		ft_printf_fd(STDOUT_FILENO, "> ");
		line = get_next_line(STDIN_FILENO);
		if (g_sig == SIGINT)
		{
			close(fd);
			free(line);
			unlink(filename);
			free(filename);
			return (NULL);
		}
		if (!line)
			break ;
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		if (is_extendable(line, 0) != -1)
			line = ft_extender(line, mini->env, mini, 0);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	write(STDOUT_FILENO, "\n", 1);
	return (filename);
}

char	*prep_heredoc_get_infile(t_parsing *head, int *cmd_count, t_mini *mini)
{
	t_parsing	*node;
	t_redir		*r;
	int			count;
	char		*tmp;

	node = head;
	count = 0;
	while (node)
	{
		r = node->redirs;
		while (r)
		{
			if (r->type == TOKEN_HEREDOC_IN)
			{
				tmp = handle_heredoc(r->file, mini);
				if (!tmp)
					return (NULL);
				free(r->file);
				r->file = tmp;
			}
			r = r->next;
		}
		node = node->next;
		count++;
	}
	*cmd_count = count;
	return ("/dev/stdin");
}

void	cleanup_heredoc(t_parsing *head)
{
	t_parsing	*node;
	t_redir		*r;

	node = head;
	while (node)
	{
		r = node->redirs;
		while (r)
		{
			if (r->type == TOKEN_HEREDOC_IN)
				unlink(r->file);
			r = r->next;
		}
		node = node->next;
	}
}
