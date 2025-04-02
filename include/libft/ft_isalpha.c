/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:31:57 by obajja            #+#    #+#             */
/*   Updated: 2024/11/18 17:32:21 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int str)
{
	if (!(str >= 'A' && str <= 'Z') && !(str >= 'a' && str <= 'z'))
		return (0);
	return (1);
}
/*
#include <stdio.h>

int	main(void)
{
	char s = 'F';

	printf("%d", ft_isalpha(s));
	return (0);
}*/