/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:31:51 by obajja            #+#    #+#             */
/*   Updated: 2024/11/18 17:38:00 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int str)
{
	if (!(str >= 'A' && str <= 'Z') && !(str >= 'a' && str <= 'z')
		&& !(str >= '0' && str <= '9'))
		return (0);
	return (1);
}
/*
#include <stdio.h>

int	main(void)
{
	char *s = "Din356osa0urs";

	printf("%d",ft_isalnum(s));
	return(0);
}*/