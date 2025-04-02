/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrhexalow.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:32:50 by obajja            #+#    #+#             */
/*   Updated: 2024/11/25 23:06:53 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbrhexalow(unsigned int n, int *count)
{
	char	*tab;

	tab = "0123456789abcdef";
	if (n >= 16)
		ft_putnbrhexalow(n / 16, count);
	*count += ft_putchar_pf(tab[n % 16]);
	return (*count);
}
/*
#include <fcntl.h>

int	main(void)
{
	int c = -2;
	ft_putnbrhexalow(c);
	return (0);
}*/
