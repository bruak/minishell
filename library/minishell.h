/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocaman <mkocaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:10:19 by mkocaman          #+#    #+#             */
/*   Updated: 2024/03/18 12:46:01 by mkocaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define CLRFUL_MINISHELL "\033[36m\033[1mminishell\033[0m\033[1m$\033[0m "
# define RED_MINISHELL "\033[31m\033[1mminishell\033[0m\033[1m$\033[0m "

# include <stdlib.h>

extern int	g_signal;

/****COMMANDS*****/
# define ECHO "echo"
# define CD "cd"
# define LOW_PWD "pwd"
# define BIG_PWD "PWD"
# define LD_PWD "OLDPWD"
# define EXPORT "export"
# define ENV "env"
# define EXIT "exit"
# define EXIT_NWLINE "exit\n"
# define UNSET "unset"
# define HOME "HOME"
# define LOW_LD_PWD "old_pwd"
# define DECLERE_X "declare -x "
# define PATH "PATH"
/***OPERATORS****/
# define SPACE ' '
# define D_SPACE " "
# define PIPET '|'
# define D_PIPET "|"
# define REDIR_OUT '>'
# define D_REDIR_OUT ">"
# define D_REDIR_OUT_2 ">>"
# define REDIR_IN '<'
# define D_REDIR_IN "<"
# define D_REDIR_IN_2 "<<"
# define NUL '\0'
# define DOT_NUL "..\0"
# define DOLLAR '$'
# define EQ '='
# define D_EQ "="
# define HYPHEN '-'
# define D_HYPHEN "-"
# define N 'n'
# define NEWLINE '\n'
# define D_NEWLINE "\n"
# define D_TILDE "~"
# define SLASH '/'
# define D_SLASH "/"
# define D_ASTERISK "*"
# define COLON ':'

/******ERR******/
# define NEWLINE_ERR "syntax error near unexpected token `newline'\n"
# define FUNNY_ERROR "its a minishell not a shell\n"
# define MALLOC_ERROR "malloc error\n"
# define ENV_ERROR "env not be received\n"
# define SYNTX_ERR "syntax error\n"
# define PWD_ERROR "env not be received"
# define FD_ERR "No such file or directory\n"
# define HOME_ERR "bash : cd: HOME not set\n"
# define BASH_CD "bash : cd: "
# define MINISHELL_EXIT "minishell: exit: too many arguments\n"
# define MINISHELL_COMMAND_NOT_FOUND "minishell: %s: command not found\n"
# define MINISHEL_FORK_ERR "minishell: fork: %s\n"
# define NOT_OPEN_ERR "was not opened"

/******SIGNAL******/
# define IF_HEREDOC_SIGNAL 10
# define IF_SIGEXIT 11
# define DO_ZERO 0

enum e_quote_type
{
	D_QUOTE = '\"',
	S_QUOTE = '\''
};

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

typedef struct s_token
{
	char				**content;
	char				*command;
	char				*before_redir;
	char				**after_redir;
	int					redir_in;
	int					redir_out;
	int					redirect;
}			t_token;

/*
* i and flag_for_export are used in ft_export.
*/
typedef struct s_data
{
	t_token			*token;
	int				flag_for_export;
	int				i;
	char			*input;
	char			**cmd;
	char			**envp;
	char			*old_pwd;
	char			**exp;
	char			*tmp;
	pid_t			pid;
	int				org_in_fd;
	int				org_out_fd;
	int				quote_count;
	int				syntax_flag;
	int				exit_code;
	t_env			*env;
	t_env			*export;
}					t_data;

// env stuff
void	*get_env(t_data *data, char **env);
void	just_env_key_value_null(t_env *env, int j);
void	initialize_env(t_data *data, char **envp);
void	starter_function(t_data *data, char **envp);
t_env	*set_exp(char **envp, int env_count);
t_env	*set_env(char **envp, int env_count);
void	set_env_key_value_null(t_env *env, int j);
void	process_env_entry(char **envp, struct s_env *env, int *j);

// is if vs
int		if_chracter_end(t_data *data, int i);
int		is_metacharacter(char c);
int		arg_count(char *str);
int		env2(t_data *data, char **tmp2);
int		is_whitespace(char c);
void	is_quote_type(t_data *data, int main_indx, char quote_type);
int		is_redir(char *str);
// parser lexer
void	handle_dquote_dollar(t_data *data, char **tmp, char **tmp2);
void	safe_free_tmp_2(t_data *data, char **tmp2, char **tmp);
void	if_not_32_and_not_whitespace(t_data *data, char **tmp, int i, int *j);
void	handle_dquote_else_side(t_data *data, char *tmp, char *tmp2);
void	little_if_isalnum_control(t_data *data, char **tmp2, int i, int *j);
void	little_just_for_compiling_tmps(char *tmp2, char *tmp);
void	little_just_for_tmp_null(char *tmp2, char *tmp);
void	if_question_mark(t_data *data, char **tmp, int *j);
int		handle_word(t_data *data, int i, int k);
int		handle_quotes(t_data *data, int main_indx, int k);
int		handle_flag(t_data *data, int i, int k);
char	*handle_dquote(t_data *data, int i, int *j, char *tmp);
char	*handle_squote(t_data *data, int i, int *j, char *tmp);
void	update_before_redir(struct s_data *data, int i, int *j);
int		process_string(char *str, int i, int count);
void	process_input(struct s_data *data, int *main_indx, int *j, int k);
char	*two_quote_cont(struct s_data *data, int i, int *j, char *tmp);
void	update_command(struct s_data *data, char *tmp, int *i);
void	process_pipe_and_redirection(struct s_data *data, int *i, int *flag,
			int *pipe_count);
void	process_command(struct s_data *data, int *cmd_i, int tokn_i,
			int *content_i);
void	pipe_counter(t_data *data);
void	token_content_allocation(t_data *data, int tokn_i, int content_i);
void	handle_input(t_data *data);
void	expander(t_data *data);
void	execute(t_data *data);
void	check_command(t_data *data, char **tmp, int i, int *j);
void	execute_with_pipe(t_data *data);
void	fork_proccesss(int fd_in, t_data *data, int i, int fd[2]);
char	*cd_env(t_data *data, char *str);
int		quote_counter(t_data *data);
// builtin
void	ft_execute(t_data *data, int j, int original_in_fd,
			int original_out_fd);
int		check_dup_and_close_fd(t_data *data, int j);
int		just_fd_error_message(char *file);
void	initialize_fds(int *j, t_data *data);
void	elif_export(t_data *data, int j);
int		handle_double_redir_out(char **content, int *i, t_data *data);
int		handle_double_redir_in(char **content, int *i, t_data *data);
int		change_dup(t_token token, t_data *data);
int		fd_control(int fd, char *file, t_data *data);
void	last_dup_and_close_fd(int originalout_fd, int originalin_fd);
void	ft_echo(char **args);
void	remove_entry(t_data *data, char *str);
void	move_export_entry(t_data *data, int i);
void	handle_low_ld_pwd(t_data *data);
void	free_and_nullify(char **key, char **value);
void	move_env_entry(t_data *data, int i);
void	ft_cd(t_data *data, char **args);
void	ft_pwd(void);
void	ft_export(t_data *data, char **arg);
void	if_there_is_no_variable(t_data *data, char **str,
			char *name, char *value);
void	if_it_already_exists(t_data *data, char *name, char **str, char *value);
void	ft_env(t_data *data);
void	ft_exit(char **args, int exit_code, t_data *data);
void	numeric_argument_required_error(char **args, int i, int *j);
void	ft_export_2(t_data *data);
void	ft_unset(t_data *data, char *str);
void	new_pwd(t_data *data);
void	*get_exp(t_data *data, char **env);
void	ft_execve(t_data *data, t_token token);
void	little_fork_error_message(t_data *data);
void	fork_proccess(char *path, char **tmp, t_data *data, t_token token);
char	*handle_squote(t_data *data, int i, int *j, char *tmp);
char	*handle_dollar(t_data *data, int i, int *j, char *tmp);
char	*handle_word2(t_data *data, int i, int *j, char *tmp);
int		is_already_exist(t_data *data, char *name);
void	rework_export(t_data *data);
void	handle_access(t_data *data, char **args);
int		is_special_arg(char *arg);
int		checker(t_data *data, int i);
char	*create_tmp(char **args, t_data *data);
int		is_content_redir(char **content, int *i);
void	if_export_flag_false(t_data *data, char *name);
void	update_export_env_value(t_data *data, char *name, char **str, int i);
void	update_export_value(t_data *data, char *name, char *value);
void	ft_export_adding_new_key2(t_data *data, char *name, char *value);
void	ft_export_adding_new_key(t_data *data, char **str, int i);
int		ft_export_input_check(t_data *data, char **str, int i);
int		ft_export_isredir_or_inputcheck(t_data *data, char **str, int i);
int		check_input(t_data *data, char *str);

//free and errors
void	free_after_redir(t_data *data, int j);
void	free_split(char **strs);
void	ft_free(t_data *data);
void	free_cmd(t_data *data);
void	free_content(t_data *data, int j);
void	erro_premium(char *str);
void	free_exp(t_data *data);
void	free_env(t_data *data);
void	free_exp(t_data *data);
void	free_env(t_data *data);
void	free_for_ctrl_d(t_data *data, int flag);
void	free_for_ctrld_and_exit(t_data *data, int exit_code);
void	free_for_crtrld_and_atoiexit(t_data *data, char **args);
//redirection
void	redir_lexer(t_data *data);
int		is_content_null_is_redir(t_data *data, int i, int j);
void	ft_redir(t_token *data);
char	*find_path(t_data *data, char *cmd);
int		heredoc(int fd, char *limiter);

//signals
void	signal_direction(int sig);
void	signal_action(void);

#endif
