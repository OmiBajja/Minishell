/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:44:43 by obajja            #+#    #+#             */
/*   Updated: 2024/11/19 16:58:00 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(const char *str);

char	*ft_strrchr(const char *str, int tofind)
{
	int	i;

	i = (ft_strlen((char *)str) - 1);
	while (str[i] && i >= 0)
	{
		if (str[i] == (unsigned char)tofind)
			return ((char *)&str[i]);
		i--;
	}
	if ((unsigned char)tofind == '\0' && str != 0)
		return ((char *)str + ft_strlen(str));
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int main ()
{
  //char* s1;
  char s2[] = "teste";
  
  printf("1%s",ft_strrchr(s2 , 'e'));
  printf("\n2%s",strrchr(s2 ,'e'));
  return (0);
}*/