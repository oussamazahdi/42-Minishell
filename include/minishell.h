/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:46:26 by hel-band          #+#    #+#             */
/*   Updated: 2024/06/26 11:46:26 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <limits.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <dirent.h>
# include <term.h>
# include <sys/ioctl.h>

/* Characteres */
# define METACHAR "<>| "
# define VAR_BLOCK " <>|?\'\"/$"
# define BLANK "\t\n\v\f\r "
# define S_QUOTE '\''
# define D_QUOTES '\"'

/* Error defines */
# define SUCCESS 0
# define FAILURE 1
# define ERRBUILTIN 2
# define ERRCMD_NOTEXEC 126
# define ERRCMD_NOTFOUNT 127
# define ERR_INVALIDARG 128
# define ERR_CTRLC 130

int	g_herdoc;
/* Lexer */
enum	e_lexeme
{
	INFILE = 1,
	OUTFILE,
	HEREDOC,
	APPEND,
	PIPE,
	BUILTIN,
	CMD,
	ARG
};

typedef struct s_token
{
	char			*content;
	char			*name;
	char			*value;
	int				type;
	bool			rm_quotes;
	bool			flag;
	struct s_token	*next;
}	t_token;

typedef struct s_exec
{
	char			**cmd;
	int				lex;
	int				fd_in;
	int				fd_out;
}			t_exec;

typedef struct s_args
{
	int		index;
	int		pipis[2];
	int		pipes[2];
}			t_args;

typedef struct s_data
{
	char	*home;
	t_list	*env;
	t_token	*env_pars;
	t_list	*token;
	t_token	*pars_token;
	int		*lexer;
	t_exec	*exec;
	int		has_cmd;
	int		has_builtin;
	int		process_count;
	int		builtin_check;
	int		len;
	t_args	*args;
	int		exit_status;
	int		*fd_heredoc;
	bool	env_flags;
	char	*last_command;
	char	*var;
}			t_data;

void	execute(t_data **data);
void	child_process(t_data *data, t_list *token, int *lexer, pid_t *pids);
void	deal_with_pipes(t_data *data);
void	get_cmd_and_args(t_list *token, int *lexer, t_data *data);
void	finally_execute(t_data *data, int fd[], pid_t *pids);
void	close_pipes(t_args *args);
void	recycle_pipe(t_args *args);
void	execute_builtin(t_data *data, t_exec *exec, pid_t *pids);
void	wait_all_processes(t_data *data, pid_t *pids, int flag);
void	verify_permission(char *copy, char **cmd, char **env);
int		verify(int result, char *str, char **cmd, char **env);
void	get_cmd_and_args(t_list *token, int *lexer, t_data *data);
void	commands_fork(t_args *args, t_data *data);

/* Builtin */
void	exit_builtin(t_data *data, pid_t *pids, char **args);
int		env_builtin(t_data *data, char **args);
int		pwd_builtin(t_data *data);
void	unset_builtin(t_data *data, char **args);
void	export_builtin(t_data *data, char **args);
// int		check_key(char *str);
int		check_key(char *var, t_data *data);
void	print_export(t_list *export, int *flag);
int		echo_builtin(t_data *data, char **args);
void	cd_builtin(t_data *data, char **args);
int		find_in_env(t_data *data, char *var);
void	handle_cd_with_args(t_data *data, char *arg);
void	check_shlvl(t_data *data);
char	*remove_plus( char *str);
t_list	*ft_lstnew_index(void *content, int index);
void	cd_dash_update_env_vars(t_data *data, char *path, char *old);
void	handle_cd_dash(t_data *data);
void	handle_cd_directory(t_data *data, char *arg);
void	sort_env(t_list *export);
int		search_key(t_list *temp, char **arr, char *var, t_data *data);
t_list	*copy_env_list(t_list *env, t_list *lst);
int		ft_check_env(t_list *env);
t_list	*ft_init_pwd(void);
int		ft_init_shlvl_and_underscore(t_list **lst);
int		ft_init_oldpwd_and_path(t_list **lst);
int		get_exit_code(char *arg, bool *error);
bool	is_quiet_mode(t_data *data);
void	update_env_var(t_list *env, char *prefix,
			char *new_value, t_data *data);

/* Redirect */
int		validate_files(t_list *token, int *lexer, int *fd_in, int *fd_out);
void	redirect_files(int fd_in, int fd_out);
void	close_files(int fd_in, int fd_out);

/* Free */
void	free_cmd_not_found(char **path, char **env, t_data *data, pid_t *pids);
void	free_builtin(t_data *data, pid_t *pids);
void	free_for_all(t_data *data);
void	free_list(t_list *list);
void	free_exec(t_exec *exec);

// char	*remove_plus(char *str);
void	handle_cd_home(t_data *data);
t_list	*ft_empty_env(void);
char	*get_env_var_value(t_list *env, char *var);
int		is_redirect(int value);
void	copy_env(t_list **list, char **env, t_data *data);
void	update_last_command(t_data *data, char *command);
char	**turn_env_to_arr(t_list *env);
char	**find_path(char **env);
int		try_paths(t_exec *exec, char **path, char **env);

// parsing
void	ft_free_double(char **ptr);
void	ft_free_all(t_data **line);
t_token	*create_token_list(char **ptr);
void	replace_or_insert_token(t_data **line, t_token **token, t_token *tmp);
void	update_token_pointers(t_token **befor, t_token **token, t_token *tmp);
t_token	*ft_add_split_to_token(t_data **line, t_token *token, \
	t_token *befor, char *read);
char	*ft_change_exp(t_data *line, char *read, char *aft, int *status);
void	ft_free_env2(t_token **line);
void	ft_add_enver(t_data *data);
void	ft_expande_export(t_data **line);
char	*ft_expande(t_data **line, char *read);
char	*ft_extract_exp(char *read, int *i, int last);
char	*ft_change(char *expande, t_token *env, t_token *tmp, t_data *line);
t_token	*ft_create_token_list(char *read);
void	ft_add_to_list(t_token *befor, char *read);
int		ft_fill_token(t_data **line, char *read);
void	ft_token_tmp(t_data **line);
void	ft_commends(t_data **line);
int		herdoc_pars(t_data **line);
void	ft_rederections(t_data **line);
t_list	*ft_lstnew_token(char *content);
t_list	*ft_lstadd_back_token(t_list **token, char *ptr);
void	ft_fill_struct(t_data **line);
int		extract_expansion_components(char *ptr, char **befor, \
	char **expande, char **after);
char	*ft_normal_expand(char *ptr, t_data **line);
int		ft_parsing(t_data **line, char *read);
int		check_quotes(t_data **line, char *read);
int		ft_protect_expand(t_data **line, t_token *token, t_token *befor);
char	*ft_remove_quots(char *read);
void	ft_quotes_remove(t_data **line);
char	**ft_split_pars(char *s, char c);
char	*ft_herdoc_expande(char *read, int i);
int		herdoc(t_data **line);
int		ft_check_herdoc_expanding(char *read);
int		ft_write_infd(t_data **line, int fd, char *file);
int		*ft_lexer(t_data **line);
t_token	*newnode_env(char *ptr);
t_token	*addback_env(t_data **line, char *ptr);
t_token	*ft_lstnew_pars(char *content);
t_token	*ft_lstadd_back_pars2(t_token *lst, char *ptr);
t_token	*ft_lstadd_back_pars(t_token *lst, char *ptr);
int		ft_exit(char *read, t_data **line);
void	handle_sigint(int sig);
void	ft_handler1(int sig);
void	ft_handler(int sig);
void	sig_int_handler(int s);
void	set_signals(void);
void	set_default_signals(void);
void	sigint_heredoc(int signal);
char	*ft_collect(t_list *tmp);
void	ft_free_tmp(t_list *tmp);
int		ft_handle_syntax(char *read, int index);
char	*ft_addspace(char *read, int index, int ptr);
int		ft_compare(char *s1, char *s2);
char	*ft_convert_to_negative(char *read);
int		ft_check_expande(char *read);
char	*ft_convert_negatives(char *read);
int		ft_check_args_spliting(char *read);
char	*ft_chifr(char *read);
char	*ft_rebuild(char *read);
char	*ft_code_double_quotes(char *read);
char	*ft_decode_double_quotes(char *read);
char	*ft_strcpy(char *src, char *dst, int start, int end);
int		ft_check_negatives(char *read);
int		ft_check_spliting(char *read);
char	*ft_dechifre(char *ptr);
char	*ft_strjoin_pars(char *s1, char *s2);
int		ft_is_syntax(int c);
int		ft_remove_spaces2(char *read);
char	*ft_remove_spaces(char *read);
int		ft_strcomp(char *src, char *cmp);
int		ft_parts_len(char *read, int start);
char	*ft_code_singel_quotes(char *read);
char	*ft_change_and_join_quotes(char *read);
void	ft_builtings(t_data **line);
char	*chefer_v2(char *read);
char	*ft_goat(char *read);
int		ft_clear_empty_nodes(t_token **token, t_token *prev);
int		ft_quotes_flag(char *read);

#endif
