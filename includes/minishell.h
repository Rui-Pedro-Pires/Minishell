/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:02:05 by ruiolive          #+#    #+#             */
/*   Updated: 2024/03/20 11:33:56 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./Libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define D_QUOTES 34
# define S_QUOTES 39

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

typedef enum e_write
{
	WRITE_TO_FILE,
	WRITE_TO_STDOUT
}					t_write;

typedef enum e_read
{
	NORMAL_ARGS,
	READ_FROM_STDIN
}					t_read;

typedef struct s_envs
{
	char			*whole_str;
	char			*name;
	char			*value;
	struct s_envs	*next;
}					t_envs;

typedef struct s_init
{
	t_envs			*envs;
	t_envs			*sorted_envs;
	char			**heardocs;
	int				heardoc_index;
	int				status;
}					t_init;

typedef struct s_data
{
	char			**command_n_args;
	t_command_type	command_type;
}					t_data;

typedef struct s_in_out
{
	char			*input_file;
	char			*output_file;
	t_input_type	input_type;
	t_output_type	output_type;
	char			*data_read;
}					t_in_out;

typedef struct s_pipes
{
	struct s_pipes	*next;
	struct s_pipes	*down;
	char			*input_string;
	char			*input_base;
	t_in_out		in_out;
	t_init			init;
	t_sign_type		pipe_type;
	t_data			data;
	bool			skip;
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

typedef enum e_error
{
	ERROR_UNFINISHED_QUOTE,
	ERROR_SPECIAL_CHAR,
	ERROR_NEWLINE,
	ERROR_SPECIAL_CHAR_DOUBLE,
	ERR_STR,
	ERR_READ,
	ERR_STR_FREE,
	ERR_FORK
}					t_error;

/****************************/
/*			PARSER			*/
/****************************/

int					parse_input(char *input, t_counter *count_struct,
						char ***heardoc_read);
int					check_begin_case_parser(char *input, int *i);
int					parser(char *input, int *i, t_counter *count_struct);
int					signs_parser(char *input, int *i);
int					quotes_parser(char *input, int *i);
int					parenthesis_parser(char *input, int *i,
						t_counter *count_struct);

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

void				creat_list(t_pipes **head, char *input, t_init init,
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
void				organize_list(t_pipes *node, int status);
t_pipes				*find_last_node(t_pipes *head);
int					parenthesis_ignore(char *input);
void				parenthesis_add(char **formated, char *input, int *i,
						int *x);
void				init_node(t_pipes *next_node, t_pipes *down_node,
						t_sign_type sign_type, t_init init);
int					define_input_and_output(t_pipes *node);
int					check_for_dbpipe_dbamper(char *input);
char				*create_str_bet_parent(char *formated);

/****************************/
/*			FREE			*/
/****************************/

void				free_args(char **args);
void				coador(t_pipes **head);
void				free_envs(t_envs *envs);
void				free_list(t_pipes **head);
void				free_input(char **input);
void				free_heardoc(t_pipes *head);

/****************************/
/*			READ LINE		*/
/****************************/

char				*line_read(char ***heardoc_read, t_counter *counter_struc,
						t_init init);
int					unfinished_command_line(char *input);
char				*str_join_with_space(char *s1, char *s2);
char				*str_join_with_newline(char *s1, char *s2);
char				*add_nl(char *s1, char *s2);
char				*creat_cwd(void);
char				*keep_reading(char *input_rec, t_counter *c_struc,
						char ***heardoc_read);

/****************************/
/*			HEARDOC			*/
/****************************/

void				heardoc_check(char ***heardoc_read, char *input,
						t_counter *count_struc, int i);
char				*search_heardoc_condition(char *input, t_counter *iter);
int					quotes_ignore(char *input);
int					maxlen(size_t new, size_t str_cond);

/****************************/
/*			TESTERZZZ		*/
/****************************/

void				input_str_tester(t_pipes *head, int type);
void				tester(t_pipes *head);

/************************************/
/*			BUILTINS				*/
/************************************/

int					ft_cd(t_pipes *node, char **str);
int					ft_pwd(void);
int					ft_echo(char **str_array);

/****************************/
/*			EXPANDER		*/
/****************************/

void				err_num_chdir(char *str);
void				ft_expander(char **str_array);
char				*check_quotes_n_expand(t_envs *head, char *str);
char				*handle_dollar_sign(t_envs *head, char *str, int j,
						bool single_open);
char				*handle_til(t_envs *head, char *str, int j);
void				update_quote_status(char c, bool *single_open,
						bool *double_open);
char				*expand(t_envs *head, char *before, char *str, char *after);
char				*check_chars(const char *str, const char *accept);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strcat(char *dest, const char *src);
void				ft_print_heardoc(char **heardoc_read);
char				*copy_inside_quotes(char *str);
size_t				ft_strnlen(const char *str, size_t maxlen);
char				*ft_strndup(const char *s, size_t n);
int					count_alphanum(char *str, int j);

/****************************/
/*			ENVS			*/
/****************************/

t_envs				*create_env_node(char *env_var);
t_envs				*create_env_list(char **env);
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

/****************************/
/*			EXECUTOR		*/
/****************************/

int					recursive_executer(t_pipes *head, int recursive);
int					execute_command(t_pipes *node);
int					ft_execve(t_pipes *node);
int					executens_ve(t_pipes *node);
char				**envlist_to_array(t_envs *envs);
int					listlen(t_envs *envs);
void				ft_exit(t_pipes *head, int exit_type);
int					recursive_down(t_pipes *head);
int					list_iterator_executer(t_pipes *head);
void				command_decider(t_pipes *node);
void				command_decider2(t_pipes *node);
int					normal_executer(t_pipes *node, char **env_array, int status);
void				init_data(t_pipes *node);
int					execute_to_stdout(t_pipes *head, int status);
int					execute_to_file(t_pipes *head, int status, int save_stdout);
int					create_path_to_execve(t_pipes *node);

/****************************/
/*			FREE			*/
/****************************/

void				simplefree(void *pnt);
void				free_pnts(void **pnts);
void				free_ppnts(void ***ppnts);
void				type_free(va_list args, const char format);
void				multiple_free(const char *format, ...);

char				*ft_strjoin_free(char *s1, char *s2);
char				*ft_strjoin_free_v2(char *s1, char *s2);

/****************************************/
/*			DEFINE INPUT OUTPUT			*/
/****************************************/

int					redirect_output_case(t_pipes *node, int i);
int					redirect_input_case(t_pipes *node);
int					append_output_case(t_pipes *node, int i);
void				rechange_str(t_pipes *node, int i, int to_skip);
char				*search_file_name(char *str);
int					heardoc(t_pipes *node, int i);
int					redirect_input(t_pipes *node, int i);
int					redirect_output(t_pipes *node, int i);
int					redir_pipe(t_pipes *node, int i);
int					append_output(t_pipes *node, int i);

/****************************************/
/*			READ FROM INPUT				*/
/****************************************/

int					read_from_stdin(t_pipes *head, char *to_be_read);
int					read_from_heardoc(t_pipes *head, char *to_be_read);
void				write_pipe_stdin(t_pipes *head, int fd_in[2],
						char *to_be_read);
void				write_pipe_heardoc(t_pipes *head, int fd_in[2],
						char *to_be_read);
void				read_pipe_stdin(t_pipes *head, int fd_in[2]);
void				read_pipe_heardoc(t_pipes *head, int fd_in[2]);

/****************************************/
/*			PIPE INPUT OUTPUT			*/
/****************************************/

int					list_size(t_pipes *head);
void				close_stdin_pipe_case(int *stdin, int **fd, int i);
void				change_stdin_pipe_case(int *stdout, int *stdin, int **fd, int i);
void				change_stdout_pipe_case(t_pipes *node, int **fd, int *stdout, int i);
void				check_for_execution_to_file(t_pipes *node, int *status, int save_stdout);
int					**alloc_memory_for_fd(int size);
void				free_fd(t_pipes *node, int **fd);
#endif