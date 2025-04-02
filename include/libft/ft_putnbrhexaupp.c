/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrhexaupp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:32:50 by obajja            #+#    #+#             */
/*   Updated: 2024/11/25 23:07:01 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbrhexaupp(unsigned int n, int *count)
{
	char	*tab;

	tab = "0123456789ABCDEF";
	if (n >= 16)
		ft_putnbrhexaupp(n / 16, count);
	*count += ft_putchar_pf(tab[n % 16]);
	return (*count);
}
/*
#include <fcntl.h>

int	main(void)
{
	int c = -30;
	ft_putnbrhexaupp(c);
	return (0);
}*/
