/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:43:30 by obajja            #+#    #+#             */
/*   Updated: 2025/04/09 12:00:00 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int tofind)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	if ((unsigned char)tofind == '\0' && !str)
		return ((char *)str + ft_strlen(str));
	while (str[i])
	{
		if (str[i] == (unsigned char)tofind)
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int main ()
{
  //char* s1;
  char s2[] = "teste";
  
  printf("1: %s",ft_strchr(s2, 'e'));
  printf("\n2: %s",strchr(s2,'e'));
  printf("\n");
  return (0);
}*/