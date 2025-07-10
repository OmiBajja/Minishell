/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:00:16 by obajja            #+#    #+#             */
/*   Updated: 2025/07/10 21:48:15 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <stdlib.h>

static int	ft_sender_fd(int fd, char s, va_list lst)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (s == 'c')
		count += ft_putchar_pfd(fd, (char)va_arg(lst, int));
	if (s == 's')
		count += ft_putstr_pfd(fd, va_arg(lst, char *));
	if (s == 'p')
		count += ft_printadress_fd(fd, va_arg(lst, unsigned long));
	if (s == 'd')
		count += ft_putnbr_pfd(fd, va_arg(lst, int), &i);
	if (s == 'i')
		count += ft_putnbr_pfd(fd, va_arg(lst, int), &i);
	if (s == 'u')
		count += ft_putnbr_upfd(fd, va_arg(lst, int), &i);
	if (s == 'x')
		count += ft_putnbrhexalow_fd(fd, va_arg(lst, unsigned int), &i);
	if (s == 'X')
		count += ft_putnbrhexaupp_fd(fd, va_arg(lst, unsigned int), &i);
	if (s == '%')
		count += ft_putchar_pfd(fd, '%');
	return (count);
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	int		i;
	va_list	lst;
	int		count;

	i = 0;
	count = 0;
	if (!str)
		return (count - 1);
	va_start(lst, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			count += ft_sender_fd(fd, str[i + 1], lst);
			i += 2;
		}
		else
		{
			ft_putchar_fd(str[i], fd);
			count += 1;
			i++;
		}
	}
	va_end(lst);
	return (count);
}

// #include <stdio.h>

// int	main(void)
// {
// 	ft_printf("%");
// 	printf("%");
// 	return (0);
// }
