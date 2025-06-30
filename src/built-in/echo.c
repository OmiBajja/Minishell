/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:47:17 by obajja            #+#    #+#             */
/*   Updated: 2025/06/30 20:55:45 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	where_print(char **inputs)
{
	int	i;
	int j;

	i = 0;
	j = -1;
	if ((inputs[1][0] && inputs[1][0] != '-')
		|| (inputs[1][1] && inputs[1][1] != 'n'))
		return (1);
	while (inputs[++i])
	{
		if (!inputs[i][1])
			return(i);
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
	if (!inputs[i][1])
		return(0);
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

void	ft_echo(char **inputs)
{
	char	*result;
	int		nl;
	int		i;

	i = 0;
	if (!inputs[1])
	{
		printf("\n");
		return ;
	}
	nl = is_newline(&inputs[1]);
	if (nl == 1 && inputs[2])
		i = where_print(&inputs[1]);
	else if (nl == 1 && !inputs[2])
		return ;
	result = ft_strscomp(&inputs[i + 1]);
	if (nl == 0)
		printf("%s\n", result);
	else
		printf("%s", result);
	free(result);
}
