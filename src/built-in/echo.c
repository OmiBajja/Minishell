/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:47:17 by obajja            #+#    #+#             */
/*   Updated: 2025/05/08 15:18:29 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void ft_echo(char **envp, char *input)
{
    int i;

    i = 0;
	while (ft_is_whitespace(input[i]))
		i++;
	if (input[i] == 'e')
	{
		i += 5;
		while (ft_is_whitespace(input[i]))
			i++;
		printf("%s\n",&input[i]);
	}
}
