/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:32:33 by obajja            #+#    #+#             */
/*   Updated: 2024/11/18 17:36:36 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int a, size_t n)
{
	unsigned int	i;
	char			*s1;

	s1 = (char *)str;
	i = 0;
	while (i < n)
	{
		s1[i] = (char)a;
		i++;
	}
	return (str);
}
/*
#include <stdio.h>
#include <string.h>

int main ()
{
  char str[50] = "I love dinosaurs they go nyooom";
  char str2[50] = "I love dinosaurs they go nyooom";
  
  ft_memset(&str[6],'A',5);
  printf("%s",str);
  memset(&str2[6],'A',5);
  printf("\n%s",str2);
  printf("\n");
  return (0);
}*/