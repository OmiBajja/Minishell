/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:02:04 by obajja            #+#    #+#             */
/*   Updated: 2025/07/09 17:44:01 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_sig = 0;

char	**default_env(void)
{
	char	**env;
	char	cwd[1024];

	env = ft_calloc(4, sizeof(char *));
	if (!env)
		return (NULL);
	getcwd(cwd, sizeof(cwd));
	env[0] = ft_strdup(cwd);
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("PATH=/usr/bin");
	return (env);
}

void	input_handler(char *input, t_mini *mini)
{
	mini->lex = lexing(input, mini);
	if (!mini->lex)
		return ;
	mini->data = token_parser(mini->lex, NULL, NULL);
	if (!mini->data)
	{
		free_tokens(mini->lex);
		mini->lex = NULL;
		return ;
	}
	exec_handler(mini->data, mini->env, mini);
	free_parse(mini->data);
	free_tokens(mini->lex);
}

int	mini_handler(t_mini *mini)
{
	char		*input;

	while (42)
	{
		input = readline("minishell :");
		if (!input)
		{
			mini_cleaner(mini);
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
	if (envp && envp[0])
	{
		mini->env = ft_strsndup(envp, ft_strslen(envp));
		if (!mini->env)
			return (EXIT_FAILURE);
	}
	else
		mini->env = default_env();
	ft_shllvl(mini);
	mini->status = 0;
	signal_handling();
	mini_handler(mini);
	return (EXIT_SUCCESS);
}
