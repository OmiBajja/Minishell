/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_upf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:32:50 by obajja            #+#    #+#             */
/*   Updated: 2024/11/25 22:14:53 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_upf(unsigned int n, int *count)
{
	if (n > 9)
		ft_putnbr_upf(n / 10, count);
	*count += ft_putchar_pf(n % 10 + '0');
	return (*count);
}
/*
#include <fcntl.h>

int	main(void)
{
	int c = 123123123;
	int fd = open("test", O_RDWR);
	if (fd == -1)
		return (1);
	ft_putnbr_fd(c, fd);
	return (0);
}*/