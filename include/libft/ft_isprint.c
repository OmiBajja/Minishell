/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:32:12 by obajja            #+#    #+#             */
/*   Updated: 2024/11/18 17:37:48 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int str)
{
	if (!(str >= 32 && str <= 126))
		return (0);
	return (1);
}
/*
#include <stdio.h>

int	main(void)
{
	char *s = "Din#.<>}{&*$sa0urs";

	printf("%d",ft_isprint(s));
	return(0);
}*/