/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:04:08 by obajja            #+#    #+#             */
/*   Updated: 2025/07/03 15:22:41 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_strndup(const char *str, size_t size)
{
	char	*new;

	new = ft_calloc(size + 1, 1);
	if (!new)
		return (NULL);
	ft_memcpy(new, str, size);
	new[size] = '\0';
	return (new);
}
