/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:02:05 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/22 15:54:46 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include "./Libft/libft.h"

# define SINGLEQUOTE 39
# define DOUBLEQUOTE 34

typedef struct s_data
{
    char            c;
    struct s_data *next;
} t_data;

void	wrong_specialch_syntax(char *input);
void    creat_list(t_data **head, char *input);
void    check_unfinished_quotes(char *input);

#endif