/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printadress_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:43:08 by obajja            #+#    #+#             */
/*   Updated: 2025/07/10 21:33:22 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putptradd_fd(int fd, unsigned long n, int *c)
{
	char	*tab;

	tab = "0123456789abcdef";
	if (n >= 16)
		ft_putptradd_fd(fd, n / 16, c);
	ft_putchar_fd(tab[n % 16], fd);
	*c += 1;
}

int	ft_printadress_fd(int fd, unsigned long ptr)
{
	int	c;

	c = 0;
	if (ptr == 0)
	{
		c += ft_putstr_pfd(fd, "(nil)");
		return (c);
	}
	ft_putstr_fd("0x", 1);
	c += 2;
	ft_putptradd_fd(fd, (unsigned long)ptr, &c);
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
