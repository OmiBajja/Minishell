/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:02:04 by obajja            #+#    #+#             */
/*   Updated: 2025/06/10 18:05:15 by pafranci         ###   ########.fr       */ 
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void input_handler(char *input, t_mini *mini)
{
    t_lex *tokens;
	t_parsing *parser;
    
    //printf("Input received: [%s]\n", input);
    tokens = lexing(input, mini->env);
    if (!tokens)
    {
        printf("Quotes please\n");
        return;
    }
    print_tokens(tokens);
	parser = token_parser(input, tokens);
	//print_all_commands(parser);
	exec_handler(parser, mini->env, mini);
    free_tokens(tokens);
}

int mini_handler(t_mini *mini)
{
    char        *input;

    while (42)
    {
        input = readline(BRED "MinisHell :" RESET_COLOR);
        // CTRL D  IS HANDLED HERE, INSTEAD OF JUST RETURN EXIT FAILURE, FREE SHIT
        if (!input)
            return (EXIT_FAILURE);
        input_handler(input,mini);
        add_history(input);
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
