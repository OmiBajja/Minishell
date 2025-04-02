/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:31:39 by obajja            #+#    #+#             */
/*   Updated: 2024/11/15 10:07:43 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *str, size_t n)
{
	unsigned int	i;
	char			*s1;

	i = 0;
	s1 = (char *)str;
	while (i < n)
	{
		s1[i] = 0;
		i++;
	}
	return (str);
}
/*
#include <stddef.h>
#include <stdio.h>
#include <string.h>

int	main(void) {
    char str[50] = "I love dinosaurs they go nyooom";
    char str2[50] = "I love dinosaurs they go nyooom";
  
    ft_bzero(&str[1], 5);
    printf("%s\n", str);
    bzero(&str2[1], 5);
    printf("%s\n", str2);
    return (0);
}*/