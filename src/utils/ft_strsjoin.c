/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:47:07 by obajja            #+#    #+#             */
/*   Updated: 2025/06/23 19:50:59 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_strsjoin(char **src, char *dest)
{
	size_t	i;
    int     size;
	char	**cpy;

	i = -1;
    size = ft_strslen(src);
    cpy = ft_calloc((size + 2), sizeof(char *));
	if (!cpy)
		return (NULL);
	while (src[++i])
	{
		cpy[i] = ft_strdup(src[i]);
		if (!cpy[i])
			return (ft_freestrs(cpy), NULL);
	}
	cpy[i] = ft_strdup(dest);
	return (cpy);
}
