/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrhexalow_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:32:50 by obajja            #+#    #+#             */
/*   Updated: 2025/07/10 21:36:57 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbrhexalow_fd(int fd, unsigned int n, int *count)
{
	char	*tab;

	tab = "0123456789abcdef";
	if (n >= 16)
		ft_putnbrhexalow_fd(fd, n / 16, count);
	*count += ft_putchar_pfd(fd, tab[n % 16]);
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
