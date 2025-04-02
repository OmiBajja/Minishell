/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:44:33 by obajja            #+#    #+#             */
/*   Updated: 2024/11/19 16:53:04 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		return (n);
	while (str1[i] && str2[i] && str1[i] == str2[i] && i < n - 1)
	{
		i++;
	}
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
/*
#include <stdio.h>
#include <string.h>

int main (void)
{
  char* s1 = "test\200";
  char* s2 = "test\0dasdasd";
  int n = 6;

  printf("%d",ft_strncmp(s1,s2,n));
  printf("\n%d",strncmp(s1,s2,n));
  return (0);
}*/