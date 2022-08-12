/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:34:17 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:34:18 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "define.h"
# include "struct.h"
# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <termios.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "readline/readline.h"
# include "readline/history.h"
# include "dirent.h"

# define MAXDIR 4096

//global
int		g_exit_status;

//1_setup
void	set_minishell(t_pair **env, char **envp);

//2_parser

//error
int		syntax_error(char *cmd);

//tokenizer
void	tokenizer(t_token **tokens, char *cmd, t_pair *env);

int		operator_token(t_token *token, char *cmd, int *i, int type);
int		simple_token(t_token *token, char *cmd, int *i);
int		quote_token(t_token *token, char *cmd, int *i);

//processer_count.c
int		processer_count(t_token *tokens);
//processer
void	processer(t_process **processes, t_token *tokens, t_pair *env);

//parser
int		parser(t_process *processes);

int		parser_env(t_process process);
int		parser_types(t_process process);
int		parser_quotes(t_process process);

void	parser_functions(t_process *process);
int		parser_heredoc(t_process *process, t_token *delimeter);
int		parser_redirect(t_process *process);
int		parser_path(t_process *process);

// 3_executor
// BUILTINS
int		echo(t_token *tokens);
int		print_envir(t_pair *env);
int		cd(t_process *process, int *i);
int		pwd(void);
void	exit_builtin(t_process *process, int *i);

t_pair	*find_alphabetic(t_pair *env, char *content);
int		contains_name(char *content, t_pair *env);
t_pair	*add_var(char *content);
int		export(t_token *tokens, t_pair *env);
t_pair	**sort_list(t_pair **env);
int		print_export(t_pair *env);
char	*check_quotes(t_token *tokens);
int		unset(t_token *tokens, t_pair *env);

// REDIRECTIONS
// close.c
void	close_not_last(t_process *process, int *i, int fd[][2]);
void	return_std(t_process *process, int *i);

//redirect_not_last.c
void	redir_1_nl_in(t_process *process, int *i, int fd[][2]);
void	redir_2_nl_in(t_process *process, int *i, int fd[][2]);
void	redir_3_nl_in(t_process *process, int *i, int fd[][2]);
void	redir_1_nl_out(t_process *process, int *i, int fd[][2]);
void	redir_2_nl_out(t_process *process, int *i, int fd[][2]);

// not_last|last
void	not_last(t_process *process, int *i);
void	last(t_process *process, int *i);

//error_exec.c
void	command_not_found(char *str);
void	permission_denied(char *str);
void	no_such_file_or_dir(char *str);
int		exec_error(char *content, char *path);

//exec.c
int		is_builtin(t_process *process, int *i);
int		check_builtins(t_process *process, int *i);
int		check_exec(char *str, int flag);
int		execute(t_process *process, int *i);

//executor.c
void	wait_signal(t_process *process, int *i);
int		built_or_exec(t_process *process, int *i);
void	simple_cmd(t_process *process);
int		executor(t_process *process);

//4_exit
void	exit_minishell(t_process *process, t_token *tokens, t_pair *env);

//0_util

//error_msg
void	fork_error(t_process *process);
void	pipe_dup_error(t_process *process);

//child_signal
void	sigint_signal(int signo);
void	sig_quit(int signo);

//signal
void	set_signal_heredoc(void);
void	set_signal(void);

//token_to_str.c
char	**token_to_str(t_token *token);

//token
t_token	*token_new(char *content, int type, int space);
void	token_add_back(t_token **head, t_token *new);
void	free_tokens(t_token *tokens);
void	token_cut(t_token **head, t_token *start, t_token *end);
t_token	*token_last(t_token *token);

//convert_env
char	**convert_to_double(t_pair *env);

//env
char	**split_env(char *env);
void	free_splitted_env(char **tmp);
int		add_env(t_pair **env, char *key, char *value);
void	free_env_pairs(t_pair *head);
t_pair	*get_env_value(t_pair *env, char *key);

//libft
int		ft_isoperator(char *cmd);
int		ft_isoperator_ch(int c);
int		ft_isblank(int c);
int		ft_isquote(int c);

int		str_is_digits(char *str);
void	free_mas(char **mas);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strnjoin(char *s1, char *s2, size_t len);
char	*ft_strjoin_free_second(char *s1, char *s2);

#endif
