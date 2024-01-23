/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:02:05 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/23 10:45:36 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "./Libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define D_QUOTES 34
#define S_QUOTES 39

typedef struct s_data
{
    int x;
} t_data;

typedef struct s_pipes
{
    struct s_pipes 	*next;
    char		    *cmd;
    int			pipe_type;
    t_data          *data;
} t_pipes;

/********************/
/*		COLORS		*/
/********************/

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

/****************************/
/*			ERRORS			*/
/****************************/

void	error_handler(int error_msg, void *param, void **param2);

typedef enum e_error
{
	ERROR_UNFINISHED_QUOTE,
    ERROR_SPECIAL_CHAR
}		t_error;

/****************************/
/*			PARSER			*/
/****************************/

void	wrong_specialch_syntax(char *input);
void    check_unfinished_quotes(char *input);
int	    quotes_check(char *input, char c);

/****************************/
/*			LIST			*/
/****************************/

void    	creat_list(t_pipes **head, char *input);

typedef enum e_pipe
{
    N,PIPE,
	S_PIPE,
	D_PIPE
}	t_pipe;

/****************************/
/*			FREE			*/
/****************************/

void    free_memory(char **args);

/****************************/
/*			STRINGS			*/
/****************************/

char    *trim_str(char *input, int *pipe_check);

#endif