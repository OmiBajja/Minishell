/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:02:04 by obajja            #+#    #+#             */
/*   Updated: 2025/06/29 14:26:53 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_sig = 0;

void	input_handler(char *input, t_mini *mini)
{
	t_lex		*tokens;
	t_parsing	*parser;

	tokens = lexing(input, mini->env);
	if (!tokens)
	{
		printf("Something's wrong\n");
		return ;
	}
	parser = token_parser(input, tokens);
	exec_handler(parser, mini->env, mini);
	free_parse(parser);
	free_tokens(tokens);
}

int	mini_handler(t_mini *mini)
{
	char		*input;

	while (42)
	{
		input = readline(BRED "MinisHell :" RESET_COLOR);
		if (!input)
		{
			if (mini->env)
				ft_freestrs(mini->env);
			if (mini)
			{
				free(mini);
				mini = NULL;
			}
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		input_handler(input, mini);
		add_history(input);
		free(input);
		input = NULL;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;

	(void)argc;
	(void)argv;
	mini = ft_calloc(1, sizeof(t_mini));
	mini->env = ft_strsndup(envp, ft_strslen(envp));
	if (!mini->env)
		return (EXIT_FAILURE);
	ft_shllvl(mini);
	mini->status = 0;
	signal_handling();
	mini_handler(mini);
	return (EXIT_SUCCESS);
}
