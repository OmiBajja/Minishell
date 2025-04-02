/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:43:08 by obajja            #+#    #+#             */
/*   Updated: 2024/11/25 23:17:03 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c);

int	ft_putstr_pf(char *s)
{
	int	i;

	if (s == NULL)
	{	
		ft_putstr_pf("(null)");
		return (6);
	}
	i = 0;
	while (s[i])
	{
		ft_putchar(s[i]);
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
