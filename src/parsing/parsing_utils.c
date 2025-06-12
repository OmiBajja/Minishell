/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:47:04 by obajja            #+#    #+#             */
/*   Updated: 2025/06/12 21:09:09 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void print_command(t_parsing *cmd) 
{
    int i = 0;
    printf("=== COMMAND ===\n");

    if (cmd->cmd)
        printf("Command: %s\n", cmd->cmd);
    else
        printf("Command: (null)\n");

    printf("Args: ");
    if (cmd->args) {
        while (cmd->args[i]) {
            printf("[%s] ", cmd->args[i]);
            i++;
        }
    } else {
        printf("(null)");
    }
    printf("\n");

    if (cmd->infile)
        printf("Infile: %s\n", cmd->infile);
    if (cmd->outfile)
        printf("Outfile: %s\n", cmd->outfile);

    printf("================\n\n");
}

void print_all_commands(t_parsing *head) 
{
    while (head) {
        printf("== PIPE ==\n");
        print_command(head);
        head = head->next;
    }
}

void free_parse(t_parsing *parse)
{
    t_parsing *tmp;

    while (parse)
    {
        tmp = parse->next;
        if (parse->cmd)
            free(parse->cmd);
        if (parse->args)
            ft_freestrs(parse->args);
        if (parse->infile)
            free(parse->infile);
        if (parse->outfile)
            free(parse->outfile);
        if (parse)
            free(parse);
        parse = tmp;
    }
}
