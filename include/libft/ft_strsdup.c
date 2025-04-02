/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:11:56 by obajja            #+#    #+#             */
/*   Updated: 2025/01/14 20:48:07 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsdup(char **src, size_t size)
{
	size_t	i;
	char	**cpy;

	i = 0;
	cpy = (char **)malloc((size + 1) * sizeof(char *));
	if (!cpy)
		return (NULL);
	while (i < size)
	{
		cpy[i] = ft_strdup(src[i]);
		if (!cpy[i])
		{
			ft_freestrs(cpy);
			return (NULL);
		}	
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}
