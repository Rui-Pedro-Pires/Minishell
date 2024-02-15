/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:31:11 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/25 11:55:22 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*build_str(char *formated, char *input);
static void	double_quotes_add(char **formated, char *input, int *i, int *x);
static void	single_quotes_add(char **formated, char *input, int *i, int *x);
static int	parenthesis_ignore(char *input);
static void	parenthesis_add(char **formated, char *input, int *i, int *x);

char	*trim_str(char *input, t_type_pipe *pipe_check, int *i)
{
	char	*formated;
	int		save;

	save = *i;
	while (input[(*i)] && input[(*i)] != '|')
	{
		if (input[(*i)] == D_QUOTES)
			(*i) += quote_ignore(input + (*i), D_QUOTES);
		else if (input[(*i)] == S_QUOTES)
			(*i) += quote_ignore(input + (*i), S_QUOTES);
		else if (input[(*i)] == '(')
			(*i) += parenthesis_ignore(input + (*i));
		(*i)++;
	}
	formated = ft_calloc(sizeof(char), (((*i) - save) + 1));
	if (!formated)
		return (NULL);
	define_pipe_type(input, pipe_check, i);
	return (build_str(formated, input + save));
}

static char	*build_str(char *formated, char *input)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	if (!input)
		return (NULL);
	while (input[i] && input[i] != '|')
	{
		if (input[i] == D_QUOTES)
			double_quotes_add(&formated, input, &i, &x);
		else if (input[i] == S_QUOTES)
			single_quotes_add(&formated, input, &i, &x);
		else if (input[i] == '(')
			parenthesis_add(&formated, input, &i, &x);
		else
		{
			formated[x] = input[i];
			x++;
			i++;
		}
	}
	return (formated);
}

static void	double_quotes_add(char **formated, char *input, int *i, int *x)
{
	(*formated)[(*x)++] = input[(*i)++];
	while (input[(*i)] && input[(*i)] != D_QUOTES)
	{
		(*formated)[(*x)] = input[(*i)];
		(*x)++;
		(*i)++;
	}
	(*formated)[(*x)++] = input[(*i)++];
}

static void	single_quotes_add(char **formated, char *input, int *i, int *x)
{
	(*formated)[(*x)++] = input[(*i)++];
	while (input[(*i)] && input[(*i)] != S_QUOTES)
	{
		(*formated)[(*x)] = input[(*i)];
		(*x)++;
		(*i)++;
	}
	(*formated)[(*x)++] = input[(*i)++];
}

void	define_pipe_type(char *input, t_type_pipe *pipe_check, int *i)
{
	if (!input[(*i)])
		*pipe_check = N_PIPE;
	else if (input[(*i) + 1] && input[(*i) + 1] == '|')
		*pipe_check = D_PIPE;
	else if (input[(*i)] && input[(*i)] == '|')
		*pipe_check = S_PIPE;
}

static int	parenthesis_ignore(char *input)
{
	int	i;
	int	parenthesis_num;

	parenthesis_num = 1;
	i = 1;
	while (input[i])
	{
		if (input[i] == '(')
			parenthesis_num++;
		else if (input[i] == ')')
			parenthesis_num--;
		if (parenthesis_num == 0)
			break ;
		i++;
	}
	return (i);
}

static void	parenthesis_add(char **formated, char *input, int *i, int *x)
{
	int	parenthesis_num;

	parenthesis_num = 1;
	(*i)++;
	while (input[(*i)])
	{
		if (input[(*i)] == '(')
			parenthesis_num++;
		else if (input[(*i)] == ')')
			parenthesis_num--;
		if (parenthesis_num == 0)
			break ;
		(*formated)[(*x)] = input[(*i)];
		(*x)++;
		(*i)++;
	}
	(*i)++;
}
