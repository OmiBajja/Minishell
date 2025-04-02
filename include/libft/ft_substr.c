/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:44:54 by obajja            #+#    #+#             */
/*   Updated: 2024/11/19 15:21:06 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(const char *str);

static	int	ft_strlen_special(const char *str, size_t len)
{
	size_t	i;

	i = 0;
	while (str[i] && i < len)
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if ((start >= (unsigned int)ft_strlen(s)) || (s[0] == '\0'))
	{
		str = malloc (1 * sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	i = 0;
	str = malloc((ft_strlen_special(&s[start], len) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (s[start] == '\0')
		return (str);
	while (s[start + i] && i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
#include <stdio.h>
int	main(void)
{
	char	s[5] = "hola";
	printf("%s", ft_substr(s, 2, 2));
  	printf("\n");
	return (0);
}*/