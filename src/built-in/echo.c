/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:47:17 by obajja            #+#    #+#             */
/*   Updated: 2025/07/01 15:21:09 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	printer(char *to_print, int	nl)
{
	int	i;

	i = -1;
	while (to_print[++i])
	{
		if (to_print[i] != '\\')
			printf("%c", to_print[i]);
	}
	if (nl == 0)
		printf("\n");
}

int	where_print(char **inputs)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	if ((inputs[1][0] && inputs[1][0] != '-')
		|| (inputs[1][1] && inputs[1][1] != 'n'))
		return (1);
	while (inputs[++i])
	{
		if (!inputs[i][1])
			return (i);
		if ((inputs[i][0] && inputs[i][0] != '-')
		|| (inputs[i][1] && inputs[i][1] != 'n'))
			return (i);
		j = 1;
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
		j = 1;
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
	if (!inputs[1])
	{
		printf("\n");
		return (1);
	}
	nl = is_newline(&inputs[1]);
	if (nl == 1 && inputs[2])
		i = where_print(&inputs[1]);
	else if (nl == 1 && !inputs[2])
		return (1);
	result = ft_strscomp(&inputs[i + 1]);
	printer(result, nl);
	free(result);
	return (0);
}
