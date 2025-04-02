/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:02:04 by obajja            #+#    #+#             */
/*   Updated: 2025/04/02 02:13:45 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void input_handler(char *input, char **envp)
{
    int i;

    i = 0;
    if (!ft_strncmp(input, "env", 4))
    {
        while (envp[i])
            printf("%s\n",envp[i++]);
    }
}

int mini_handler(char **envp)
{
    char        *input;

    while (42)
    {
        input = readline(BRED "MinisHell :" RESET_COLOR);
        if (!input)
            return (EXIT_FAILURE);
        input_handler(input, envp);
        add_history(input);
        free(input);
    }
    return (EXIT_SUCCESS);
}

int main(int argc, char **argv, char **envp)
{
    char        **dup_env;
    
    (void)argc;
    (void)argv;
    dup_env = ft_strsdup(envp, ft_strslen(envp));
    if (!dup_env)
        return (EXIT_FAILURE);
    signal_handling();
    mini_handler(dup_env);
    return (EXIT_SUCCESS);
}
