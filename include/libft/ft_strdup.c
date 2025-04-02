/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:43:41 by obajja            #+#    #+#             */
/*   Updated: 2024/11/19 11:08:10 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(const char *src);

char	*ft_strdup(const char *src)
{
	int		i;
	char	*cpy;

	i = 0;
	cpy = malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!cpy)
		return (NULL);
	while (src[i])
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
/*
#include <string.h>
int	main(void)
{
	char	s1[50]= "Dinosaurs Nyoo02m";
	printf("%s", ft_strdup(s1));
  printf("\n%s", strdup(s1));
  printf("\n");
	return (0);
}*/