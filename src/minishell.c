/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:02:04 by obajja            #+#    #+#             */
/*   Updated: 2025/05/28 23:16:00 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void input_handler(char *input, t_mini *mini)
{
    t_lex *tokens;
	t_parsing *parser;
    
    //printf("Input received: [%s]\n", input);
    tokens = lexing(input);
    if (!tokens)
        printf("No tokens generated\n");
    //print_tokens(tokens);
	parser = token_parser(input, tokens, mini->env);
	//print_all_commands(parser);

	exec_handler(parser, mini->env);
    free_tokens(tokens);
}

int mini_handler(t_mini *mini)
{
    char        *input;

    while (42)
    {
        input = readline(BRED "MinisHell :" RESET_COLOR);
        if (!input)
            return (EXIT_FAILURE);
        input_handler(input,mini);
        add_history(input);
        printf("DInosaur\n");
        //rl_on_new_line();
        //rl_replace_line("",0);
        free(input);
    }
    return (EXIT_SUCCESS);
}

int main(int argc, char **argv, char **envp)
{
    t_mini  mini;

    (void)argc;
    (void)argv;
    mini.env = ft_strsdup(envp, ft_strslen(envp));
    if (!mini.env)
        return (EXIT_FAILURE);
    signal_handling();
    mini_handler(&mini);
    return (EXIT_SUCCESS);
}
