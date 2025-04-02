/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:32:42 by obajja            #+#    #+#             */
/*   Updated: 2024/11/19 01:03:30 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd);

void	ft_putendl_fd(char *s, int fd)
{
	int		i;
	char	nl;

	nl = '\n';
	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	ft_putchar_fd(nl, fd);
}
/*
#include <fcntl.h>

int	main(void)
{
	char c[44] = "DinosaursNyooom";
	int fd = open("test", O_RDWR);
	if (fd == -1)
		return (1);
	ft_putendl_fd(c, fd);
	return (0);
}*/