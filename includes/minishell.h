/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:02:05 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/23 14:43:18 by ruiolive         ###   ########.fr       */
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
	ERROR_SPECIAL_CHAR
}					t_error;

/****************************/
/*			PARSER			*/
/****************************/

void				wrong_specialch_syntax(char *input);
void				check_unfinished_quotes(char *input);
int					quotes_check(char *input, char c);

/****************************/
/*			LIST			*/
/****************************/

void				creat_list(t_pipes **head, char *input);

/****************************/
/*			FREE			*/
/****************************/

void				free_memory(char **args);

/****************************/
/*			STRINGS			*/
/****************************/

char				*trim_str(char *input, t_type_pipe *pipe_check);

#endif