/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:32:28 by obajja            #+#    #+#             */
/*   Updated: 2024/11/19 10:57:08 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	unsigned int	i;
	char			*dest_cpy;
	const char		*src_cpy;

	if ((dest == 0 && src == 0) || (size == 0))
		return (dest);
	dest_cpy = (char *)dest;
	src_cpy = (const char *)src;
	if (dest_cpy > src_cpy && dest_cpy < src_cpy + size)
	{
		i = size;
		while (--i > 0)
			dest_cpy[i] = src_cpy[i];
		dest_cpy[0] = src_cpy[0];
	}
	else
	{
		i = 0;
		while (i < size)
		{
			dest_cpy[i] = src_cpy[i];
			i++;
		}
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	src[] = "lorem ipsum dolor sit amet";
	char	src2[] = "lorem ipsum dolor sit amet";

	char	*dest;
	char	*dest2;

	dest = src + 1;
	dest2 = src2 + 1;
	ft_memmove(dest,src, 8);
	memmove(dest2,src2, 8);
  printf("%s",src);    
  printf("\n%s",src2);
  printf("\n");
  return (0);
}*/