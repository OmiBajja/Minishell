/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:02:13 by obajja            #+#    #+#             */
/*   Updated: 2025/06/24 16:29:38 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>

//=== Token Types ===//
#define TOKEN_UNKOWN     0
#define TOKEN_COMMAND    1
#define TOKEN_PIPE       2
#define TOKEN_REDIR_IN   3
#define TOKEN_REDIR_OUT  4

//=== Struct Definitions ===//
typedef struct s_lex
{
	char 	*value;
	int 	type;
	struct s_lex *next;
} t_lex;

typedef struct s_parsing
{
	char *outfile;
	char *infile;
	char *cmd;
	char **args;
	t_lex *lex;
	struct s_parsing *next;
} t_parsing;

typedef struct s_mini
{
	char **env;
	int		status;
	t_parsing *data;
} t_mini;

//=== Lexer Functions ===//
t_lex   *lexing(char *input, char **env);
t_lex   *create_token(char *value, int type);
void    add_to_list(t_lex **head, t_lex *new);
char    *word_lexer(char *input, int *start, char **env);
void    print_tokens(t_lex *tokens);
void    free_tokens(t_lex *tokens);

//=== Parser Functions ===//
void        parser(char *input, t_mini *mini);
t_parsing   *token_parser(char *input, t_lex *tokens);
t_parsing   *create_parse();
char        **new_args(char **args, char *new_arg);
t_lex       *command_processor(t_parsing *cmd, t_lex *tokens);
t_lex       *redirection_machine(t_parsing *cmd, t_lex *tokens);
void        command_machine(t_parsing *cmd, t_lex *token);
void        print_all_commands(t_parsing *head);
void 		free_parse(t_parsing *parse);

//=== Core Functions ===//
short   ft_init_list(char *input, t_mini *mini);
void    signal_handling(void);
void    exec_handler(t_parsing *head, char **envp, t_mini *mini);

//=== Built-in Commands ===//
char *ft_get_env_val(char **env, const char *key);
void ft_replace_env(char ***env, const char *key, const char *value);
void ft_cd(t_mini *mini, char **args);
void ft_echo(char **input);
void ft_env(char **envp);
void ft_pwd(char **env);
void ft_export(t_mini *mini, char **command);
void ft_unset(t_mini *mini, char *command);
void ft_exit(t_mini *mini, char **args);

//=== Execution & Pipes ===//
void    pipex(char *infile, char *outfile, char **cmds, int cmd_count, char **env);
int     **create_pipes(int n);
void    close_pipes(int **pipes, int n);
void    child_process(int index, int infile_fd, int outfile_fd, char *cmd, char **env, int **pipes, int cmd_count);
void    exec_cmd(char const *cmd, char const *paths, char **env);

//=== Environment Helpers ===//
char    *find_env_paths(char **env);
char    *find_cmd_in_pahts(const char *cmd, char **env_paths_tab);
void 	ft_shllvl(t_mini  *mini);


//=== String & Utility Functions ===//
char    **ft_split_str_mini(char *str, char *charset, t_mini *mini);
int     ft_is_whitespace(int str);
char    *ft_strndup(char *str, size_t size);
int     operator_check(char c);
int     find_operator(char c);

//=== Libft Extensions / Utils ===//
int     ft_strlen(const char *s);
char    *ft_strjoin(char const *s1, char const *s2);
char    *ft_substr(char const *s, unsigned int start, size_t len);
char    *ft_strnstr(const char *haystack, const char *needle, int n);
bool    is_needle_in_haystack(const char *haystack, const char *needle);
char    **ft_split_pau(char const *s, char c);
char    **ft_strsjoin(char **src, char *dest);
char 	*ft_strscomp(char **src);

//=== Memory & Error Handling ===//
void    free_tab(char **tab);
void    perror_exit(void);
void    command_not_found_exit(char **cmd_tab);
void    invalid_usage_exit(int ac);

//=== Quote & Env Expansion Handling ===//
char    *ft_extender(char *input, char **env);
int     is_extendable(char *input);
int     ft_quotechecker(char *input);
char    *ft_dequoter(char *input);
char    *quote_handler(char *input, int *index, char **env);

extern int g_sig;

// typedef struct s_data
// {
// 	char	*paths;
// 	char	**env;
// }	t_env_data;

//int		pipes_and_forks(t_env_data env_data, char *av[]);