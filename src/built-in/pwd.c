/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:53:56 by obajja            #+#    #+#             */
/*   Updated: 2025/07/12 00:41:01 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_pwd(void)
{
	char	cwd[1024];
	char	*pwd;

	pwd = getcwd(cwd, sizeof(cwd));
	if (pwd)
		ft_printf_fd(1, "%s\n", pwd);
	else
	{
		ft_printf_fd(2, "pwd: error retrieving current directory: getcwd: can");
		ft_printf_fd(2, "not parent directories: No such file or directory\n");
	}
	return (0);
}
