/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:02:13 by obajja            #+#    #+#             */
/*   Updated: 2025/07/15 16:29:56 by pafranci         ###   ########.fr       */
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
#include <sys/stat.h>
#include <termios.h>

//=== Token Types ===//
#define TOKEN_UNKOWN     	0
#define TOKEN_COMMAND    	1
#define TOKEN_PIPE       	2
#define TOKEN_REDIR_IN   	3
#define TOKEN_REDIR_OUT  	4
#define TOKEN_HEREDOC_IN 	5
#define TOKEN_APPEND_OUT 	6
#define EXPORT_IGNORE		50
#define EXPORT_REPLACE		51
#define EXPORT_ADD_BOTH		52
#define EXPORT_ADD_EXPORT	53
#define EXPORT_ADD_ENV		54

//=== Struct Definitions ===//
typedef struct s_lex
{
	char			*value;
	int				type;
	struct s_lex	*next;
}	t_lex;

typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_parsing
{
	struct s_redir		*redirs;
	char				*cmd;
	char				**args;
	t_lex				*lex;
	struct s_parsing	*next;
}	t_parsing;

typedef struct s_mini
{
	char			**env;
	int				status;
	t_parsing		*data;
	t_lex			*lex;
	char			**export;
	char			**exp_dup;
	int				saved_in;
	int				saved_out;
	struct termios	saved_termios;
}	t_mini;

typedef struct s_child
{
	t_parsing	*cmds;
	pid_t		*pid;
	char		*infile_path;
	int			cmd_count;
	int			**pipes;
	char		**env;
	int			i;
}	t_child;

typedef struct s_pipex
{
	t_parsing	*cmds;
	t_mini		*mini;
	pid_t		*pid;
	t_child		*child;
	char		*infile;
	int			cmd_count;
	char		**env;
}	t_pipex;

//=== Lexer Functions ===//
t_lex		*lexing(char *input, t_mini *mini);
t_lex		*create_token(char *value, int type);
int			add_to_list(t_lex **head, t_lex *new);
char		*word_lexer(char *input, int *start, t_mini *mini);
char		*unquote_handler(char *input, int *i, t_mini *mini);
char		*word_handler(char *input, int *i, t_mini *mini);
void		print_tokens(t_lex *tokens);
void		free_tokens(t_lex *tokens);

//=== Parser Functions ===//
t_parsing	*token_parser(t_lex *tkn, t_parsing *h, t_parsing *n, t_mini *m);
t_parsing	*create_parse(void);

void		parser(char *input, t_mini *mini);
char		**new_args(char **args, char *new_arg);
char		**create_args(char *first_arg);
t_lex		*command_processor(t_parsing *cmd, t_lex *tokens, t_mini *mini);
t_lex		*redirection_machine(t_parsing *cmd, t_lex *tokens, t_mini *mini);
void		append_redir(t_parsing *cmd, int type, char *file);
int			command_machine(t_parsing *cmd, t_lex *token);
void		print_all_commands(t_parsing *head);
void		free_parse(t_parsing *parse);

//=== Core Functions ===//
short		ft_init_list(char *input, t_mini *mini);
void		signal_handling(void);
void		exec_handler(t_parsing *head, char **envp, t_mini *mini);

//=== Built-in Commands ===//
int			ft_cd(t_mini *mini, char **args);
int			ft_echo(char **input);
int			ft_env(char **envp);
int			ft_pwd(void);
int			ft_export(t_mini *mini, char **command);
int			ft_unset(t_mini *mini, char **command);
int			ft_exit(t_mini *mini, char **args);

//=== Execution & Pipes ===//
void		pipex(t_pipex *pipex);
int			**create_pipes(int n);
void		close_pipes(int **pipes, int n);
void		child_process(t_child *child, t_mini *mini);
int			setup_redirs_list(t_redir *r, t_child *child, t_mini *mini);
void		apply_redirs(t_child *child, t_parsing *cmd, t_mini *mini);
void		exec_cmd(char **cmd_args, char const *paths,
				t_mini *mini, t_child *child);
bool		is_builtin(const char *cmd);
void		close_saved_inout(t_mini *mini);

//=== Pipex Helpers ===//
void		free_pipex(int **pipes, int cmd_count, pid_t *pid);
t_parsing	*get_nth_node(t_parsing *head, int n);
void		wait_for_children(pid_t *pid, int cmd_count, t_mini *mini);

//=== Heredoc Helpers ===//
char		*handle_heredoc(const char *delim, t_mini *mini);
char		*prep_heredoc_get_infile(t_parsing *head,
				int *cmd_count, t_mini *mini);
void		cleanup_heredoc(t_parsing *head);

//=== Environment Helpers ===//
char		*find_env_paths(char **env);
char		*find_cmd_in_pahts(const char *cmd, char **env_paths_tab);
int			ft_replace_env(char ***env, const char *key, const char *value);
void		ft_shllvl(t_mini *mini);
int			ft_export_checker(char *str);
char		**ft_export_expand(char **env_sorted);
int			export_replacer(t_mini *mini, char *to_replace, int equals_index);
int			env_replacer(t_mini *mini, char *to_replace, int equals_index);
char		**ft_env_sort(char **export_list);
char		*exporter_expander(char *new_env, char *env_sorted);
int			add_to_exp(t_mini *mini, char *arg, int result);
void		print_and_free(char **export_list);
void		export_printer(t_mini *mini);
int			is_it_in_env(char **exp_list, char *to_find);
int			is_to_add_replace(char **env, char *word);
int			replace_to_exp(t_mini *mini, char *to_replace, int equals_index);
char		*status_code(t_mini *mini);

//=== String & Utility Functions ===//
int			ft_is_whitespace(int str);
char		*ft_strndup(const char *str, size_t size);
int			operator_check(const char *input);
int			find_operator(const char *str);

//=== Libft Extensions / Utils ===//
int			ft_strlen(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strnstr(const char *haystack, const char *needle, int n);
bool		is_needle_in_haystack(const char *haystack, const char *needle);
char		**ft_split_pau(char const *s, char c);
char		**ft_strsjoin(char **src, char *dest);
char		*ft_strscomp(char **src);

//=== Memory & Error Handling ===//
void		free_tab(char **tab);
void		perror_exit(void);
void		cmd_not_found_exit(char **cmd_tab, t_mini *mini, t_child *child);
void		invalid_usage_exit(int ac);
void		mini_cleaner(t_mini *mini);
void		master_cleaner(t_mini *mini, t_child *child);
void		free_null(char *to_free);
void		child_cleaner(t_child *child, t_mini *mini);

//=== Quote & Env Expansion Handling ===//
char		*ft_extender(char *input, char **env, t_mini *mini, int quotes);
int			is_extendable(char *input, int quotes);
int			ft_quotechecker(char *input);
char		*ft_dequoter(char *input);
char		*quote_handler(char *input, int *index, char **env, t_mini *mini);

extern int	g_sig;
