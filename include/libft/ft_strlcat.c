/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:44:07 by obajja            #+#    #+#             */
/*   Updated: 2024/11/19 16:55:28 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(const char *str);

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	r;

	i = ft_strlen(dst);
	j = 0;
	r = ft_strlen(src);
	if (size <= i)
		return (size + r);
	r += i;
	while (j < (size - i - 1) && src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (r);
}
/*
#include <stdio.h>
#include <bsd/string.h>

int	main(void)
{
	char	*dest;
	//char	s2[16] = "lorem";
	//char	dest2[1] = "a";
	//char	s4[16] = "lorem";
	if (!(dest = (char *)malloc(sizeof(*dest) * 15)))
          return (0);
    memset(dest, 0, 15);
    memset(dest, 'r', 6);

	dest[11] = 'a';
	ft_strlcat(dest, "lorem ipsum", 15);

	//printf("%ld", ft_strlcat(s1, "", 15));
	//printf("\n%ld", strlcat(s3, "", 15));
	printf("\nTest:%s",dest);
	//printf("\nVrai:%s",s3);
	return (0);
}*/