/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dequoter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:43:05 by obajja            #+#    #+#             */
/*   Updated: 2025/06/11 16:13:32 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int ft_quotechecker(char *quote)
{
    if (quote[0] == '\'' || quote[0] == '"')
        return (1);
    else
        return (0);
}

char *ft_dequoter(char *quote)
{
    int i;
    int j;
    int size;
    char *result;

    j = -1;
    i = 0;
    size = ft_strlen(quote);
    result = ft_calloc(size - 1, 1);
    while (++j < size)
        result[j] = quote[++i];
    free(quote);
    return (result);
}
