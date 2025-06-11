/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:30:23 by obajja            #+#    #+#             */
/*   Updated: 2025/06/11 17:13:32 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *single_quote_handler(char *input, int *index)
{
    char *quote;
    int fin;

    fin = *index;
    while (input[++fin])
    {
        if (input[fin] == '\'')
        {
            quote = ft_strndup(&input[*index], fin - *index);
            if (!quote)
                return (NULL);
            quote = ft_dequoter(quote);
            *index = fin + 1;
            return(quote);
        }
    }
    return (NULL);
}

char *double_quote_handler(char *input, int *index, char **env)
{
    char *quote;
    int fin;

    fin = *index;
    while (input[++fin])
    {
        if (input[fin] == '"')
        {
            quote = ft_strndup(&input[*index], fin - *index);
            if (!quote)
                return (NULL);
            if (is_extendable(quote) != -1)
                quote = ft_extender(quote, env);
            quote = ft_dequoter(quote);
            *index = fin + 1;
            return(quote);
        }
    }
    return (NULL);
}

char *quote_handler(char *input, int *index, char **env)
{
    char *quote;

    if (input[*index] == '\'')
        quote = single_quote_handler(input, index);
    else if (input[*index] == '"')
        quote = double_quote_handler(input, index, env);
    return(quote);
}
