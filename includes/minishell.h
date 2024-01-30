/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:02:05 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/30 14:40:48 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./Libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
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

typedef enum e_error
{
	ERROR_UNFINISHED_QUOTE,
	ERROR_SPECIAL_CHAR,
	ERROR_WRONG_INPUT
}					t_error;

/****************************/
/*			PARSER			*/
/****************************/

int					wrong_specialch_syntax(char *input);
int					check_unfinished_quotes(char *input);
int					quotes_check(char *input, char c);
int					count_rarrow(char *str);
void				organize_list(t_pipes *pipe_struct);
int					count_larrow(char *str);
int					count_amperz(char *str);
int					check_input(char *input, int *i);
int					check_for_command(char *input);
int					check_pipe_amper_next(char *input);
int					check_if_command_exits(char *input);
char				**special_splitens(char *str, int *back, int *front,
						char c);

/****************************/
/*			LIST			*/
/****************************/

void				creat_list(t_pipes **head, char *input);

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

char				*line_read(void);
int					unfinished_str(char *input);
void				count_parenthesis(char *input, int *parenthesis);
int					parse_input(char *input);
char				*ft_strjoin_v2(char *s1, char *s2);
char				*creat_cwd(void);

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

/****************************/
/*			TESTERZZZ		*/
/****************************/

void				tester(t_pipes *head);
void				input_str_tester(t_pipes *head);

#endif