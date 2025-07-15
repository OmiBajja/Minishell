/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:02:04 by obajja            #+#    #+#             */
/*   Updated: 2025/07/15 17:03:32 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_sig = 0;

char	**default_env(void)
{
	char	**env;
	char	*pwd;
	char	cwd[1024];

	env = ft_calloc(4, sizeof(char *));
	if (!env)
		return (NULL);
	pwd = getcwd(cwd, sizeof(cwd));
	if (!pwd)
		return (NULL);
	env[0] = ft_strdup(cwd);
	env[1] = ft_strdup("SHLVL=0");
	if (!env[1])
		return (free(env[0]), NULL);
	env[2] = ft_strdup("PATH=/usr/bin");
	if (!env[2])
		return (ft_freestrs(env), NULL);
	return (env);
}

void	input_handler(char *input, t_mini *mini)
{
	mini->lex = lexing(input, mini);
	if (!mini->lex)
		return ;
	mini->data = token_parser(mini->lex, NULL, NULL, mini);
	if (!mini->data)
	{
		free_tokens(mini->lex);
		mini->lex = NULL;
		return ;
	}
	exec_handler(mini->data, mini->env, mini);
	tcsetattr(STDERR_FILENO, TCSANOW, &mini->saved_termios);
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
			ft_printf_fd(STDOUT_FILENO, "exit\n");
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
	if (!mini)
		return (EXIT_FAILURE);
	tcgetattr(STDERR_FILENO, &mini->saved_termios);
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
