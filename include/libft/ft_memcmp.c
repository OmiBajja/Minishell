/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:27:10 by obajja            #+#    #+#             */
/*   Updated: 2024/11/18 21:41:08 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t size)
{
	size_t	i;
	char	*src1;
	char	*src2;

	src1 = (char *)ptr1;
	src2 = (char *)ptr2;
	i = 0;
	if (size == 0)
		return (size);
	while (src1[i] == src2[i] && i < size - 1)
	{
		i++;
	}
	return ((unsigned char)src1[i] - (unsigned char)src2[i]);
}
/*
#include <string.h>
#include <stdio.h>
int main()
{
  char s1[50] = "DinosNyoom";
  char s2[50] = "DisnoNyoom";
  printf("%d",ft_memcmp(s1,s2,15));
  printf("\n%d",memcmp(s1,s2,15));

  return 0;
}*/
