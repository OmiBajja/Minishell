/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:02:04 by obajja            #+#    #+#             */
/*   Updated: 2025/04/10 01:04:57 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <signal.h>

int     g_ok = 0;

void	ctrlc_handler()
{
    g_ok = 130;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("",0);
    rl_redisplay();
}

void signal_handling()
{
    struct sigaction	ear;

    sigemptyset(&ear.sa_mask);
    ear.sa_handler = ctrlc_handler;
    ear.sa_flags = SA_RESTART;
    sigaction(SIGINT, &ear, NULL);
    ear.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &ear, NULL);
}