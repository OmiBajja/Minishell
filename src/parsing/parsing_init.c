/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:40:03 by obajja            #+#    #+#             */
/*   Updated: 2025/04/15 18:15:22 by obajja           ###   ########.fr       */
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

char **new_args(char **args, char *new_arg)
{
	char **all_args;
	int i;

	i = 0;
	if (!args)
    {
        all_args = malloc(sizeof(char *) * 2);
        if (!all_args)
            return (NULL);
        all_args[0] = ft_strdup(new_arg);
        all_args[1] = NULL;
        return (all_args);
    }
	while (args[i])
		i++;
	all_args = malloc (sizeof(char *) * (i + 2));
	if (!all_args)
		return (NULL);
	i = -1;
	while (args[++i])
		all_args[i] = args[i];
	all_args[i] = ft_strdup(new_arg);
	all_args[i + 1] = NULL;
	free(args);
	return (all_args);
}

t_parsing *create_parse()
{
	t_parsing *parse;
	
	parse = malloc(sizeof(t_parsing));
	if (!parse)
		return (NULL);
	parse->outfile = NULL;
	parse->infile = NULL;
	parse->cmd = NULL;
	parse->args = NULL;
	parse->next = NULL;

	return (parse);
}
void  command_machine(t_parsing *cmd, t_lex *token, char **env)
{
	char *input;

	if (is_extendable(token->value) != -1)
	{
		input = ft_extender(token->value,env);
		if (!cmd->cmd)
		{
			cmd->cmd = input;
			cmd->args = new_args(NULL, input);
		}
		else
			cmd->args = new_args(cmd->args, input);
	}

	else if (!cmd->cmd)
	{
		cmd->cmd = ft_strdup(token->value);
		cmd->args = new_args(NULL, token->value);
	}
	else
		cmd->args = new_args(cmd->args, token->value);
}

t_lex *redirection_machine(t_parsing *cmd, t_lex *tokens)
{
	t_lex *next;

	next = tokens->next;
	if (next == NULL || next->type != TOKEN_COMMAND)
	{
		printf("Broski where the filename at?\n");
		return (NULL);
	}
	if (tokens->type == TOKEN_REDIR_IN)
		cmd->infile = ft_strdup(next->value);
	else if (tokens->type == TOKEN_REDIR_OUT)
		cmd->outfile = ft_strdup(next->value);
	return (next);
}

t_lex *command_processor(t_parsing *cmd, t_lex *tokens, char **env)
{
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (tokens->type == TOKEN_COMMAND)
			command_machine(cmd, tokens, env);
		else if (tokens->type == TOKEN_REDIR_IN || tokens->type == TOKEN_REDIR_OUT)
			tokens = redirection_machine(cmd, tokens);
		tokens = tokens->next;
	}
	return (tokens);
}