/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printadress.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:43:08 by obajja            #+#    #+#             */
/*   Updated: 2024/11/25 20:13:40 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c);

void	ft_putptradd(unsigned long n, int *c)
{
	char	*tab;

	tab = "0123456789abcdef";
	if (n >= 16)
		ft_putptradd(n / 16, c);
	ft_putchar_fd(tab[n % 16], 1);
	*c += 1;
}

int	ft_printadress(unsigned long ptr)
{
	int	c;

	c = 0;
	if (ptr == 0)
	{
		c += ft_putstr_pf("(nil)");
		return (c);
	}
	ft_putstr_fd("0x", 1);
	c += 2;
	ft_putptradd((unsigned long)ptr, &c);
	return (c);
}
/*
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int c = -68;
	char f = 's';
	ft_printadress((unsigned long)&f);
	printf("\n%p",(void *)&f);
	return (0);
}*/
