/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:43:49 by obajja            #+#    #+#             */
/*   Updated: 2024/11/14 18:43:51 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "libft.h"

static void f (unsigned int i, char * s)
{
    if (i % 2 == 0 && *s >= 'a' && *s <= 'z')
        *s -= 32;
}
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}
/*
int	main(void)
{
    char s[]="dinosaurs";
    ft_striteri(s,f);
    printf("%s",s);
    printf("\n");
    return (0);
}*/