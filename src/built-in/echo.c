/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:47:17 by obajja            #+#    #+#             */
/*   Updated: 2025/07/15 14:43:30 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	printer(char *to_print, int nl)
{
	int	i;
	int	err;

	i = -1;
	err = 1;
	if (!to_print)
		return (1);
	while (to_print[++i] && err == 1)
		err = write(STDOUT_FILENO, &to_print[i], 1);
	if (err != 1)
	{
		ft_printf_fd(2, "Minishell: echo: write");
		ft_printf_fd(2, " error: No space left on device\n");
		return (1);
	}
	if (nl == 0)
		ft_printf_fd(STDOUT_FILENO, "\n");
	return (0);
}

int	where_print(char **inputs)
{
	int	i;
	int	j;

	i = 0;
	if (!inputs[1])
		return (1);
	if (ft_strlen(inputs[1]) < 2 || inputs[1][0] != '-'
		|| inputs[1][1] != 'n')
		return (1);
	while (inputs[++i])
	{
		if (!inputs[i][1])
			return (i);
		if ((inputs[i][0] && inputs[i][0] != '-')
		|| (inputs[i][1] && inputs[i][1] != 'n'))
			return (i);
		j = 0;
		while (inputs[i][++j])
		{
			if (inputs[i][j] != 'n')
				return (i);
		}
	}
	return (i);
}

int	is_newline(char **inputs)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!inputs[i][0] || !inputs[i][1])
		return (0);
	if ((inputs[i][0] && inputs[i][0] != '-')
		|| (inputs[i][1] && inputs[i][1] != 'n'))
		return (0);
	else
	{
		while (inputs[i][++j])
		{
			if (inputs[i][j] != 'n')
				return (0);
		}
		return (1);
	}
}

int	ft_echo(char **inputs)
{
	char	*result;
	int		nl;
	int		i;

	i = 0;
	if (!inputs)
		return (EXIT_FAILURE);
	if (!inputs[0] || !inputs[1])
	{
		ft_printf_fd(STDOUT_FILENO, "\n");
		return (EXIT_SUCCESS);
	}
	nl = is_newline(&inputs[1]);
	if (nl == 1 && inputs[2])
		i = where_print(&inputs[1]);
	else if (nl == 1 && !inputs[2])
		return (EXIT_FAILURE);
	result = ft_strscomp(&inputs[i + 1]);
	if (!result)
		return (EXIT_FAILURE);
	i = printer(result, nl);
	if (i == 1)
		return (free(result), EXIT_FAILURE);
	free(result);
	return (EXIT_SUCCESS);
}
