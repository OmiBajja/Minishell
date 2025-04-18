/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:04:08 by obajja            #+#    #+#             */
/*   Updated: 2025/04/14 11:07:04 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<minishell.h>

char *ft_strndup(char *str, size_t size)
{
	char *new;
	
	new = malloc(size + 1);
	if (!new)
		return(NULL);
	ft_memcpy(new, str, size);
	new[size] = '\0';
	return (new);
}