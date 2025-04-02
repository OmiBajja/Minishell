/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:44:39 by obajja            #+#    #+#             */
/*   Updated: 2024/11/25 12:01:32 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(const char *str);

char	*ft_strnstr(const char *str, const char *tofind, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (n < 0)
		n = ft_strlen(str);
	if (tofind[j] == '\0')
		return ((char *)str);
	while (str[i] && i < n)
	{
		j = 0;
		while (str[i + j] == tofind[j] && (i + j) < n)
		{
			j++;
			if (tofind[j] == '\0')
				return ((char *)&str[i]);
		}
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int main ()
{
  char* s1 = "I love dinosaurs";
  char* s2 = "in";
  
  printf("1 %s",ft_strnstr(s1, s2,3));
  return (0);
}*/
