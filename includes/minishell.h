/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:02:05 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/22 16:11:50 by ruiolive         ###   ########.fr       */
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
    struct s_data *next;
    char c;
} t_data;

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

/****************************/
/*			LIST			*/
/****************************/

void    creat_list(t_data **head, char *input);

/****************************/
/*			FREE			*/
/****************************/

void    free_memory(char **args);

#endif