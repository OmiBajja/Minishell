/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_pfd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:32:37 by obajja            #+#    #+#             */
/*   Updated: 2025/07/10 21:29:59 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_pfd(int fd, char c)
{
	write(fd, &c, 1);
	return (1);
}
/*
#include <fcntl.h>

int	main(void)
{
	char c = 'f';
	int fd = open("test", O_RDWR);
	if (fd == -1)
		return (1);
	ft_putchar_fd(c, fd);
	return (0);
}*/