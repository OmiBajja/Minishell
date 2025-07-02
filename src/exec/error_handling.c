/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:38:41 by pafranci          #+#    #+#             */
/*   Updated: 2025/07/02 23:48:21 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void	perror_exit(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	command_not_found_exit(char **cmd_tab, t_mini *mini, t_child *child)
{
    write(2, cmd_tab[0], ft_strlen(cmd_tab[0]));
    write(2, ": command not found\n", 20);
    if (mini->data)
        free_parse(mini->data);
    if (mini->lex)
        free_tokens(mini->lex);
    if (child)
    {
        free_pipex(child->infile_fd, child->pipes, child->cmd_count, child->pid);
        free(child);
    }
    mini_cleaner(mini);
    exit(127);
}

void	invalid_usage_exit(int ac)
{
	if (ac < 5)
		write(2, "Error: Too few arguments.\n", 26);
	else
		write(2, "Error: Too many arguments.\n", 27);
	write(2, "Usage: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 45);
	exit(EXIT_FAILURE);
}
