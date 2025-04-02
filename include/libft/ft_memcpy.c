/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:32:22 by obajja            #+#    #+#             */
/*   Updated: 2024/11/19 11:03:12 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	unsigned int	i;
	char			*dest_cpy;
	const char		*src_cpy;

	if ((dest == 0 && src == 0) || (size == 0))
		return (dest);
	dest_cpy = (char *)dest;
	src_cpy = (const char *)src;
	i = 0;
	while (i < size)
	{
		dest_cpy[i] = src_cpy[i];
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
  //char* src = (void*)0;
  //char dest[50];
  //char dest2[50];

  ft_memcpy((void*)0,(void*)0,3);
  memcpy((void*)0,(void*)0,3);
  //printf("%s",dest);
  //printf("\n%s",dest2);
  //printf("\n");
  return (0);
}*/