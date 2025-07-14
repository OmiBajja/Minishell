/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 09:16:35 by pafranci          #+#    #+#             */
/*   Updated: 2025/07/14 14:25:34 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <readline/history.h>

static int	heredoc_loop(const char *delim, char *f_name, int fd, t_mini *mini)
{
	char	*line;
	int		len;

	while (42)
	{
		ft_printf_fd(STDOUT_FILENO, "> ");
		line = get_next_line(STDIN_FILENO);
		if (g_sig == SIGINT)
			return (close(fd), free(line), unlink(f_name), free(f_name), 1);
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
		ft_printf_fd(fd, "%s\n", line);
		free(line);
	}
	return (0);
}

char	*handle_heredoc(const char *delim, t_mini *mini)
{
	int		fd;
	char	*f_name;

	f_name = ft_strdup("/tmp/.minishell_heredoc");
	if (!f_name)
		return (NULL);
	fd = open(f_name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
		return (perror("heredoc"), free(f_name), NULL);
	if (heredoc_loop(delim, f_name, fd, mini) == 1)
		return (NULL);
	close(fd);
	ft_printf_fd(STDOUT_FILENO, "\n");
	return (f_name);
}

char	*prep_heredoc_get_infile(t_parsing *head, int *cmd_count, t_mini *mini)
{
	t_parsing	*node;
	t_redir		*r;
	int			count;
	char		*tmp;

	node = head;
	count = 0;
	while (node && ++count >= 0)
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
	}
	return (*cmd_count = count, "/dev/stdin");
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
