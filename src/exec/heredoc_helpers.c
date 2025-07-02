/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 09:16:35 by pafranci          #+#    #+#             */
/*   Updated: 2025/07/02 18:56:16 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*handle_heredoc(const char *delim)
{
	char	*line;
	int		fd;
	char	*filename;

	filename = ft_strdup("/tmp/.minishell_heredoc");
	if (!filename)
		return (NULL);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
		return (perror("heredoc"), NULL);
	while (42)
	{
		line = readline("> ");
		if (!line || !strcmp(line, delim))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (filename);
}

char	*prep_heredoc_get_infile(t_parsing *head, int *cmd_count)
{
	t_parsing	*node;
	char		*infile;

	node = head;
	infile = NULL;
	*cmd_count = 0;
	while (node)
	{
		if (node->heredoc_delim)
			node->heredoc_file = handle_heredoc(node->heredoc_delim);
		if (node->infile && !infile && !node->heredoc_file)
			infile = node->infile;
		node = node->next;
		(*cmd_count)++;
	}
	if (infile)
		return (infile);
	else
		return ("/dev/stdin");
}

void	cleanup_heredoc(t_parsing *head)
{
	t_parsing	*node;

	node = head;
	while (node)
	{
		if (node->heredoc_file)
			unlink(node->heredoc_file);
		node = node->next;
	}
}
