/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:47:31 by obajja            #+#    #+#             */
/*   Updated: 2025/06/28 05:48:21 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exiting(t_mini *mini, int exit_val)
{
	if (mini->env)
		ft_freestrs(mini->env);
	if (mini)
	{
		free(mini);
		mini = NULL;
	}
	exit(exit_val);
}

int	num_check(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
	}
	return (0);
}

void	ft_exit(t_mini *mini, char **args)
{
	printf("exit\n");
	if (args[1])
	{
		if (num_check(args[1]))
		{
			printf("Minishell: exit: %s: numeric argument required\n", args[1]);
			exiting(mini, 2);
		}
		if (args[2])
		{
			printf("Minishell: exit: too many arguments\n");
			return ;
		}
		if (!args[2])
			exiting(mini, ft_atoi(args[1]));
	}
	else
		exiting(mini, mini->status);
}
