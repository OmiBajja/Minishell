/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:02:13 by obajja            #+#    #+#             */
/*   Updated: 2025/04/15 18:18:45 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

#define TOKEN_UNKOWN	0
#define TOKEN_COMMAND	1
#define TOKEN_PIPE		2
#define TOKEN_REDIR_IN	3
#define TOKEN_REDIR_OUT	4

typedef struct s_lex
{
	char *value;
	int	  type;
	struct s_lex *next;
}	t_lex;

typedef struct s_parsing
{
    char *outfile;
    char *infile;
    char *cmd;
    char **args;
	struct s_parsing *next;
	t_lex *lex;

}   t_parsing;

typedef struct s_mini
{
    char **env;
    t_parsing *data;


}   t_mini;

void    signal_handling();
short   ft_init_list(char *input, t_mini *mini);
void    ft_env(char **envp);
void    parser(char *input, t_mini  *mini);
char    **ft_split_str_mini(char *str, char *charset, t_mini  *mini);
int		ft_is_whitespace(int str);
t_lex 	*lexing (char *input);
char 	*ft_strndup(char *str, size_t size);
int		operator_check(char c);
int		find_operator(char c);
t_lex 	*create_token(char *value, int type);
void 	add_to_list(t_lex **head, t_lex *new);
char 	*word_lexer(char *input, int *start);
void 	print_tokens(t_lex *tokens);
void 	free_tokens(t_lex *tokens);
t_lex 	*command_processor(t_parsing *cmd, t_lex *tokens);
t_lex 	*redirection_machine(t_parsing *cmd, t_lex *tokens);
void  	command_machine(t_parsing *cmd, t_lex *token);
t_parsing *create_parse();
char 	**new_args(char **args, char *new_arg);
t_parsing *token_parser(char *input, t_lex *tokens);
void print_all_commands(t_parsing *head);
