/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:32:08 by obajja            #+#    #+#             */
/*   Updated: 2024/11/18 17:36:49 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int str)
{
	if (!(str >= '0' && str <= '9'))
		return (0);
	return (1);
}
/*
#include <stdio.h>

int	main(void)
{
	char *s = "0973";

	printf("%d",ft_isdigit(s));
	return(0);
}*/