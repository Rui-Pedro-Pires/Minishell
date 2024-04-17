/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:50:15 by jorteixe          #+#    #+#             */
/*   Updated: 2024/04/11 10:50:15 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./Libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define D_QUOTES 34
# define S_QUOTES 39

extern int			g_return_value;

typedef enum e_command_type
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	NOT_BUILTIN,
	NO_COMMAND
}					t_command_type;

typedef enum e_sign_type
{
	N_PIPE,
	S_PIPE,
	D_PIPE,
	AMPER
}					t_sign_type;

typedef enum e_input_type
{
	HEARDOC,
	REDIRECT_INPUT,
	NO_INPUT
}					t_input_type;

typedef enum e_output_type
{
	APPEND_OUTPUT,
	REDIRECT_OUTPUT,
	NO_OUTPUT
}					t_output_type;

typedef struct s_envs
{
	char			*whole_str;
	char			*name;
	char			*value;
	bool			has_equal;
	struct s_envs	*next;
}					t_envs;

typedef struct s_init
{
	t_envs			*envs;
	t_envs			*sorted_envs;
	char			**heardocs;
	int				*heardoc_index;
	pid_t			*pid;
	int				status;
}					t_init;

typedef struct s_data
{
	char			**command_n_args;
	t_command_type	command_type;
}					t_data;

typedef struct s_in_out
{
	int				fd_in;
	int				fd_out;
	t_input_type	input_type;
	t_output_type	output_type;
}					t_in_out;

typedef struct s_pipes
{
	struct s_pipes	*next;
	struct s_pipes	*down;
	char			*input_string;
	t_in_out		in_out;
	t_init			*init;
	t_sign_type		pipe_type;
	t_data			data;
}					t_pipes;

typedef struct s_counter
{
	int				i;
	int				counter;
	int				empty;
	int				prnt;
}					t_counter;

/********************/
/*		COLORS		*/
/********************/

# define RED "\x1B[31m"
# define GRN "\x1B[32m"
# define YEL "\x1B[33m"
# define BLU "\x1B[34m"
# define MAG "\x1B[35m"
# define CYN "\x1B[36m"
# define WHT "\x1B[37m"
# define RESET "\x1B[0m"

/****************************/
/*			ERRORS			*/
/****************************/

void				error_handler(int error_msg, void *param, void **param2);
void				err_hlr_2(int error_msg, void *param, void **param2);
char				*string_error(char *input);
void				print_error(char *str);
void				print_error_char(char str);

typedef enum e_error
{
	ERROR_UNFINISHED_QUOTE,
	ERROR_SPECIAL_CHAR,
	ERROR_NEWLINE,
	ERROR_SPECIAL_CHAR_DOUBLE,
	ERR_STR,
	ERR_READ,
	ERR_STR_FREE,
	ERR_FORK,
	ERR_WILDCARD
}					t_error;

/****************************/
/*			PARSER			*/
/****************************/

int					parse_input(char *input, t_counter *count_struct,
						t_init *init);
int					check_begin_case_parser(char *input, int *i);
int					parser(char *input, int *i, t_counter *count_struct);
int					signs_parser(char *input, int *i);
int					quotes_parser(char *input, int *i);
int					parenthesis_parser(char *input, int *i,
						t_counter *count_struct);

/****************************/
/*			MAIN			*/
/****************************/

void				initialize(t_init *init);
void				process_input(t_pipes **head, char *input, t_init *init);

/****************************/
/*			QUOTES			*/
/****************************/

int					quote_ignore(char *input, char c);
int					quote_check(char *input, int *i, char c);

/****************************/
/*			SIGNS			*/
/****************************/

int					check_signs(char *input, int *i, char **myChar);
int					amper_count(char *input, int *i);
int					pipe_count(char *input, int *i);
int					major_sig_count(char *input, int *i);
int					minor_sig_count(char *input, int *i);
char				*pipe_amper_search(char *input);
char				*signs_search(char *input);
char				*signs_case(char *input);
int					pipe_checker(char *input, int *x, char **myChar);
int					amper_checker(char *input, int *x, char **myChar);
int					major_checker(char *input, int *x, char **myChar);
int					minor_checker(char *input, int *x, char **myChar);
int					ft_return_check(char *input, int *i, int *x);
char				*check_minor_case_special_error(char *input, int i);

/****************************/
/*		PARENTHESIS				*/
/****************************/

char				*parenthesis_search(char *input);
int					check_for_error_bf_parenthesis(char *input, int i);
int					check_for_error_af_parenthesis(char *input, int i);
int					search_correct_parenthesis(char *input);
int					count_parenthesis(char *input, t_counter *counter_struc);
int					check_valid_parenthesis(char *input);

/****************************/
/*		PARSER	UTILS		*/
/****************************/

int					check_cmd_aft(char *input);
int					check_cmd_end(char *input);
int					check_end(char *input);
char				*search_char(char *input);
bool				search_command(char *input, int *i,
						int correct_parenthesis);
bool				search_dpipe_or_damper(char *input, int *i,
						int correct_parenthesis);

/****************************/
/*			LIST			*/
/****************************/

void				creat_list(t_pipes **head, char *input, t_init *init,
						int status);
char				*trim_str(char *input, t_sign_type *pipe_check, int *i,
						int status);
char				*build_str(char *formated, char *input, int status);
void				double_quotes_add(char **formated, char *input, int *i,
						int *x);
void				single_quotes_add(char **formated, char *input, int *i,
						int *x);
void				define_pipe_type(char *input, t_sign_type *sign_type,
						int *i);
t_pipes				*find_last_node(t_pipes *head);
int					parenthesis_ignore(char *input);
void				parenthesis_add(char **formated, char *input, int *i,
						int *x);
void				init_node(t_pipes *next_node, t_pipes *down_node,
						t_init *init);
int					define_input_and_output(t_pipes *node);
int					check_for_dbpipe_dbamper(char *input);
char				*create_str_bet_parent(char *formated);

/****************************/
/*			FREE			*/
/****************************/

void				free_args(char **args);
void				free_envs(t_envs *envs);
void				free_list(t_pipes **head);
void				free_input(char **input);
void				free_heardoc(t_pipes *head);

/****************************/
/*			READ LINE		*/
/****************************/

char				*line_read(t_init *init);
int					unfinished_command_line(char *input);
char				*str_join_with_space(char *s1, char *s2, int free_type);
char				*str_join_with_newline(char *s1, char *s2);
char				*creat_cwd(void);
char				*trim_cwd(char *trimmed_cwd);
void				create_cwd_from_envs(char **pwd, char **cwd, t_init init);
char				*keep_reading(char *input_rec, t_counter *c_struc,
						t_init *init, int *fd);
void				status_update(int status);

/****************************/
/*			HEARDOC			*/
/****************************/

int					heardoc_check(t_init *init, char *input,
						t_counter *count_struc, int i);
char				*search_heardoc_condition(char *input, t_counter *iter);
int					quotes_ignore(char *input);
char				*read_heardoc_buffer(int fd);
char				*expande_heardoc(t_init init, char *str);
int					maxlen(size_t new, size_t str_cond);
char				*handle_dollar_sign_heardoc(t_init init, char *str, int j);

/************************************/
/*			BUILTINS				*/
/************************************/

int					ft_cd(t_pipes *node, char **str);
int					handle_cd_home(t_pipes *node, char **str);
int					handle_cd_too_many_args(void);
int					handle_cd_new_dir(t_pipes *node, char *new_dir);
void				update_old_pwd(t_pipes *node);
void				update_current_pwd(t_pipes *node);
int					cd_home(t_pipes *node, char **str);
int					ft_pwd(t_pipes *node);
int					ft_echo(char **str_array);

/****************************/
/*			EXPANDER		*/
/****************************/

void				err_num_chdir(char *str);
char				*check_quotes_n_expand(t_init init, char *str);
char				*handle_dollar_sign(t_init init, char *str, int j,
						bool single_open);
char				*handle_til(t_init init, char *str, int j);
void				update_quote_status(char c, bool *single_open,
						bool *double_open);
char				*expand(t_init init, char *before, char *str, char *after);
char				*check_chars(const char *str, const char *accept);
char				*copy_inside_quotes(char *str);
size_t				ft_strnlen(const char *str, size_t maxlen);
char				*ft_strndup(const char *s, size_t n);
int					count_alphanum(char *str, int j);
char				*handle_questionmark(t_init init, char *str, int j);
char				*expand_questionmark(t_init init, char *before,
						char *after);
char				*expand_tilde(t_init init, char *before, char *after);

/****************************/
/*			ENVS			*/
/****************************/

t_envs				*create_env_node(char *env_var, bool shlvl_to_change);
t_envs				*create_env_list(char **env, bool shlvl_to_change);
int					ft_env(t_envs *head);
void				free_env_list(t_envs *head);
void				free_split_array(char **array);
int					ft_export(t_pipes *node, char **str_array);
bool				export_is_valid(char *str);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_unset(t_envs **head, t_envs **head_sorted,
						char **str_array);
t_envs				*find_prev_node(t_envs *head, char *str);
void				remove_node(t_envs **head, t_envs *prev, t_envs *current);
void				free_nodes(t_envs *node);
char				*ft_getenv(t_envs *head, char *str);
t_envs				*bubble_sort(t_envs *head);
int					ft_is_only_digit(char *str);
void				shlvl_change(char **env_var);
void				update_env_last_arg(t_pipes *node);
void				update_sorted_env_last_arg(t_pipes *node);

/****************************/
/*			EXECUTOR		*/
/****************************/

void				loop_list_and_execute(t_pipes *curr, t_pipes *head,
						int size, int *status);
int					recursive_executer(t_pipes *current, int recursive,
						t_pipes *head);
int					child_process(t_pipes *curr, t_pipes *head, int i,
						int stdin);
int					execute_command(t_pipes *node);
int					executens_ve(t_pipes *node);
int					single_command(t_pipes *curr, t_pipes *head);
char				**envlist_to_array(t_envs *envs);
int					listlen(t_envs *envs);
void				ft_exit(t_pipes *head, int exit_type, char **args_array);
int					recursive_down(t_pipes *curr, t_pipes *head);
int					list_iterator_executer(t_pipes *curr, t_pipes *head);
void				command_decider(t_pipes *node);
void				command_decider2(t_pipes *node);
int					init_data(t_pipes *node);
char				*create_path_to_execve(t_pipes *node);

/****************************/
/*			FREE			*/
/****************************/

void				simplefree(void *pnt);
void				free_pnts(void **pnts);
void				free_ppnts(void ***ppnts);
void				type_free(va_list args, const char format);
void				multiple_free(const char *format, ...);
void				free_resources(t_pipes *head);
void				handle_too_many_args(int *exit_type);
void				handle_numeric_arg(int *exit_type, char *arg);
bool				ft_str_is_number(char *str);
char				*ft_strjoin_free(char *s1, char *s2);
char				*ft_strjoin_free_v2(char *s1, char *s2);

/****************************************/
/*			DEFINE INPUT OUTPUT			*/
/****************************************/

int					redirect_output_case(t_pipes *node, int i);
int					append_output_case(t_pipes *node, int i);
void				rechange_str(t_pipes *node, int i, int to_skip);
char				*search_file_name(t_pipes *node, char *str);
int					heardoc(t_pipes *node, int i);
int					redirect_input(t_pipes *node, int i);
int					redirect_output(t_pipes *node, int i);
int					redir_pipe(t_pipes *node, int i);
int					append_output(t_pipes *node, int i);

/****************************************/
/*			READ FROM INPUT				*/
/****************************************/

int					write_pipe_stdin(t_pipes *head);
void				write_pipe_heardoc(t_pipes *head);

/****************************************/
/*			PIPE INPUT OUTPUT			*/
/****************************************/

int					list_size(t_pipes *head);
void				check_for_execution_to_file(t_pipes *node, int *status);
char				**ft_split_ignore_quotes(char *s, char *c);
int					all_quotes_ignore(char *s);
char				*listfiles(char *dirname);
int					array_size(char **file);

/****************************************/
/*				SIGNALS					*/
/****************************************/

void				iterative_mode(void);
void				reset_signals(void);
void				update_signals_status(void);
void				update_sigint_status(void);
void				reset_sigint(void);
void				handle_status_sigquit(int sig);
void				handle_status_sigint(int sig);
void				handle_sigint(int sig);

/****************************************/
/*				WILDCARDS				*/
/****************************************/

char				*trim_files(char *files, char *str_condition);
int					search_redir(char *str, int i);
int					redir_wildcard(t_pipes *node, int *i, char *files,
						char **str_condition);
char				*wildcards(t_pipes *node, char *files);
void				insert_trimmed_files(char **trimmed_files,
						char *file_to_add);
int					starts_with_file_name(char *file, char *condition);
char				*get_mid(char *str, int *i);
int					middle_with_file_name(char *file, char *condition);
int					all_cases_file_name(char *file, char *condition);
int					check_to_add(char *file, char *condition);
char				*push_char(char *str, char to_push);
char				*remove_dupp_wild(char *condition);
int					ends_with_file_name(char *file, char *condition);
char				*wildcard_checker(char *str, int *i);
int					check_only_wildcard(char *str_condition);
int					insert_files_into_str(t_pipes *node, char *files, int *i,
						int save_redir);

#endif