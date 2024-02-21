/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:02:05 by ruiolive          #+#    #+#             */
/*   Updated: 2024/02/01 10:24:23 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./Libft/libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
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
	NOT_BUILTIN
}					t_command_type;

typedef enum e_special_char
{
	S_LEFT_ARROW,
	D_LEFT_ARROW,
	S_RIGHT_ARROW,
	D_RIGHT_ARROW,
	AMPERZ,
	NO_SPECIAL
}					t_special_char;

typedef enum e_type_pipe
{
	N_PIPE,
	S_PIPE,
	D_PIPE
}					t_type_pipe;

typedef struct s_data
{
	char			*path_command;
	char			**command_n_args;
	struct s_envs	*envs;
	t_special_char	special_char;
	t_command_type	command_type;
}					t_data;

typedef struct s_pipes
{
	struct s_pipes	*next;
	char			*input_string;
	t_type_pipe		pipe_type;
	t_data			*data;
	bool			empty_node;
}					t_pipes;

typedef struct s_counter
{
	int				i;
	int				counter;
	int				empty;
	int				prnt;
}					t_counter;

typedef struct s_envs
{
	char			*name;
	char			*value;
	struct s_envs	*next;
}					t_envs;

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
	ERR_STR_FREE
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

void				creat_list(t_pipes **head, char *input);
void				define_pipe_type(char *input, t_type_pipe *pipe_check,
						int *i);

/****************************/
/*			FREE			*/
/****************************/

void				free_args(char **args);
void				coador(t_pipes **head);

/****************************/
/*			STRINGS			*/
/****************************/

char				*trim_str(char *input, t_type_pipe *pipe_check, int *i);

/****************************/
/*			READ LINE		*/
/****************************/

char				*line_read(char ***heardoc_read, t_counter *counter_struc);
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

/****************************/
/*			DATA			*/
/****************************/

int					command_decider1(t_data *data);
int					command_decider2(t_data *data);
int					fill_data(t_pipes *pipe_struct, int count);
int					count_rarrow(char *str);
int					count_larrow(char *str);
int					count_amperz(char *str);
int					count_input(t_pipes *pipe);
void				prepare_split(t_data *data, t_pipes *pipe, int *back,
						int *front);
void				check_specialz(char *str, t_data *data, int *front);
int					check_only_spaces(char *input_str);
int					word_counter(char const *s, char c);
void				organize_list(t_pipes *pipe_struct);
char				**special_splitens(char *str, int *back, int *front,
						char c);

/****************************/
/*			TESTERZZZ		*/
/****************************/

void				freezzzz(char *input, char ***heardoc_read, t_pipes **head);
void				input_str_tester(t_pipes *head);

/************************************/
/*			BUILTINS				*/
/************************************/

void				ft_cd(t_envs *head, char **str);
void				ft_pwd(void);
void				ft_echo(t_envs *head, char **str_array);

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
void				ft_env(t_envs *head);
void				free_env_list(t_envs *head);
void				free_split_array(char **array);
void				ft_export(t_envs *head, char **str_array);
bool				export_is_valid(char *str);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_unset(t_envs **head, char **str_array);
t_envs				*find_prev_node(t_envs *head, char *str);
void				remove_node(t_envs **head, t_envs *prev, t_envs *current);
void				free_nodes(t_envs *node);
char				*ft_getenv(t_envs *head, char *str);

#endif