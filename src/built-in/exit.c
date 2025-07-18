/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:47:31 by obajja            #+#    #+#             */
/*   Updated: 2025/07/12 21:49:24 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exiting(t_mini *mini, int exit_val)
{
	if (mini->data)
		free_parse(mini->data);
	if (mini->lex)
		free_tokens(mini->lex);
	mini_cleaner(mini);
	exit(exit_val);
}

int	num_check(char *str)
{
	int	i;

	i = -1;
	if (!ft_isdigit(str[0]))
	{
		if (str[0] == '-' || str[0] == '+')
			i++;
		else
			return (1);
	}
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
	}
	return (0);
}

int	ft_exit(t_mini *mini, char **args)
{
	int	exit_code;

	ft_printf_fd(STDOUT_FILENO, "exit\n");
	if (args[1])
	{
		if (num_check(args[1]) == 1)
		{
			ft_printf_fd(2, "Minishell: exit: %s: numeric argument required\n",
				args[1]);
			exiting(mini, 2);
		}
		if (args[2])
		{
			ft_printf_fd(2, "Minishell: exit: too many arguments\n");
			return (1);
		}
		if (!args[2])
		{
			exit_code = ft_atoi(args[1]) % 256;
			exiting(mini, exit_code);
		}
	}
	else
		exiting(mini, mini->status);
	return (0);
}
