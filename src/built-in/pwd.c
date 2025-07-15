/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:53:56 by obajja            #+#    #+#             */
/*   Updated: 2025/07/15 14:43:39 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_pwd(void)
{
	char	cwd[1024];
	char	*pwd;
	int		err;

	pwd = getcwd(cwd, sizeof(cwd));
	if (pwd)
	{
		err = write(STDOUT_FILENO, pwd, ft_strlen(pwd));
		if (err != -1)
			err = write(STDOUT_FILENO, "\n", 1);
	}
	else
	{
		ft_printf_fd(2, "pwd: error retrieving current directory:");
		ft_printf_fd(2, "getcwd: cannot parent directories:");
		ft_printf_fd(2, " No such file or directory\n");
		return (1);
	}
	if (err == -1)
	{
		ft_printf_fd(2, "Minishell: pwd: write");
		ft_printf_fd(2, " error: No space left on device\n");
		return (1);
	}
	return (0);
}
