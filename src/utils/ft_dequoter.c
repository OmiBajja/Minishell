/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dequoter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:43:05 by obajja            #+#    #+#             */
/*   Updated: 2025/07/01 10:23:40 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_quotechecker(char *quote)
{
	if (quote[0] == '\'' || quote[0] == '"')
		return (1);
	else
		return (0);
}

char	*ft_dequoter(char *quote)
{
	int		i;
	int		j;
	int		size;
	char	*result;

	i = 0;
	j = -1;
	size = ft_strlen(quote);
	result = ft_calloc(size, 1);
	if (!result)
		return (free(quote), NULL);
	while (++j < size)
		result[j] = quote[++i];
	free(quote);
	return (result);
}
