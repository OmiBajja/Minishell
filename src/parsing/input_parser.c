/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:48:21 by obajja            #+#    #+#             */
/*   Updated: 2025/04/09 23:48:27 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

short ft_init_list(char *input, t_mini *mini)
{
    mini->data = malloc(sizeof (t_data));
    if (!mini->data)
        return (EXIT_FAILURE);
    mini->data->bltins = malloc((7)*sizeof(char*));
    mini->data->bltins[0] = "echo";
    mini->data->bltins[1] = "cd";
    mini->data->bltins[2] = "pwd";
    mini->data->bltins[3] = "export";
    mini->data->bltins[4] = "unset";
    mini->data->bltins[5] = "env";
    mini->data->bltins[6] = "exit";
    parser(input, mini);
    return(EXIT_SUCCESS);

}

void parser(char *input, t_mini  *mini)
{
    int i;
    int j;

    i = 0;
    j = 0;
    (void)input;
    (void)mini;
    mini->data->buffer= ft_split_str(input, " \t\v\n\f\b");
    mini->data->buffer= ft_split_str_mini(input, "|&<>", mini);
}