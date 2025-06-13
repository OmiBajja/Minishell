/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strscomp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 21:49:46 by obajja            #+#    #+#             */
/*   Updated: 2025/06/13 22:25:31 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int     ft_strsstrlen(char **src)
{
    int     i;
    int     size;
    
    i = -1;
    size = 0;
    while (src[++i])
    {
        size += ft_strlen(src[i]);
        if (src[i + 1])
            size += 1;
    }
    return (size);
}

char *ft_strscomp(char **src)
{
    int     i;
    int     size;
    char    *result;
    
    i = -1;
    size = ft_strsstrlen(src);
    result = ft_calloc(size + 1, 1);
    while (src[++i])
    {
        ft_strlcat(result,src[i],size + 1);
        if (src[i + 1])
            ft_strlcat(result," ",size + 1);
    }
    return(result);
}
