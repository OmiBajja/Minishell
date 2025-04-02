/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:27:10 by obajja            #+#    #+#             */
/*   Updated: 2024/11/18 16:40:44 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int searchedChar, size_t size)
{
	size_t	i;
	char	*src;
	char	tofind;

	src = (char *)str;
	tofind = (char)searchedChar;
	i = 0;
	while (i < size)
	{
		if (src[i] == tofind)
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}
/*
#include <string.h>
#include <stdio.h>
int main()
{
  char src[50] = "DinosAAZEAEZAEAZaurs";
  char nt = 'E';
  printf("%p",ft_memchr(src,nt,15));
  printf("\n%p",memchr(src,nt,15));

  return 0;
}*/
