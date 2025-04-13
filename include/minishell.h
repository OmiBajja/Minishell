/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:02:13 by obajja            #+#    #+#             */
/*   Updated: 2025/04/09 23:05:28 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_data
{
    char **cmd_list;
    char **bltins;
    char **buffer;
    char **outfile;
    char **infile;
    char **cmd;
    char **arg;

}   t_data;

typedef struct s_mini
{
    char **env;
    t_data *data;


}   t_mini;

void    signal_handling();
short   ft_init_list(char *input, t_mini *mini);
void    ft_env(char **envp);
void    parser(char *input, t_mini  *mini);
char    **ft_split_str_mini(char *str, char *charset, t_mini  *mini);

