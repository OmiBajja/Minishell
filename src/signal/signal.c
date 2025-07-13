/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:02:04 by obajja            #+#    #+#             */
/*   Updated: 2025/07/13 23:44:35 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <signal.h>

static void	ctrlc_handler(int sig)
{
	g_sig = sig;
	write(STDOUT_FILENO, "\n", 1);
}

void	signal_handling(void)
{
	struct sigaction	ear;

	sigemptyset(&ear.sa_mask);
	ear.sa_handler = ctrlc_handler;
	ear.sa_flags = 0;
	sigaction(SIGINT, &ear, NULL);
	ear.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &ear, NULL);
}
