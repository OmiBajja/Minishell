/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:47:17 by obajja            #+#    #+#             */
/*   Updated: 2025/06/28 16:07:31 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_echo(char **inputs)
{
	char	*result;
	int		i;
	int		n;
	int		j;

	i = -1;
	n = 0;
	while (inputs[++i])
	{
		j = 3;
		if (ft_strncmp(inputs[i], "-n", 2) == 0)
			while (inputs[i][j] == 'n')
				j++;
		if (inputs[i][j])
			break ;
		n = 1;
	}
	result = ft_strscomp(&inputs[i]);
	if (n == 0 && i == 0)
		printf("%s\n", result);
	else
		printf("%s", result);
	free(result);
}
