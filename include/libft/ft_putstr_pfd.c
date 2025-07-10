/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_pfd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:43:08 by obajja            #+#    #+#             */
/*   Updated: 2025/07/10 21:47:01 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_putstr_pfd(int fd, char *s)
{
	int	i;

	if (s == NULL)
	{
		ft_putstr_pfd(fd, "(null)");
		return (6);
	}
	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	return (i);
}
/*
#include <fcntl.h>
int	main(void)
{
	char c[44] = "DinosaursNyooom";
	int fd = open("test", O_RDWR);
	if (fd == -1)
		return (1);
	ft_putstr_fd(c, fd);
	return (0);
}*/
