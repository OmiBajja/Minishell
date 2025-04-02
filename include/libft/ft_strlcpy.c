/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:44:13 by obajja            #+#    #+#             */
/*   Updated: 2024/11/19 16:55:21 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i] && i < size - 1 && size != 0)
	{
		dst[i] = src[i];
		i++;
	}
	if (size != 0)
		dst[i] = '\0';
	while (src[i])
	{
		i++;
	}
	return (i);
}
/*
#include <bsd/string.h>

int main (void)
{
	char	dest[6] = "Hello" ;
	char	dest2[6] = "Hello" ;
	char	src[19] = "lorem ipsum";
	char	src2[30] = "lorem ipsum";
	unsigned int size = 0;
	
	ft_strlcpy (dest, src, size);
	printf("\nMa   fonction:%s",dest);
	strlcpy (dest2, src2, size);
	printf("\nVrai fonction:%s",dest2);
	return(0);
}*/