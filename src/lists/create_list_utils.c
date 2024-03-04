/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive  <ruiolive@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:18:54 by ruiolive          #+#    #+#             */
/*   Updated: 2024/02/26 13:18:54 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*build_str(char *formated, char *input, int status);
static void	double_quotes_add(char **formated, char *input, int *i, int *x);
static void	single_quotes_add(char **formated, char *input, int *i, int *x);
static void	define_pipe_type(char *input, t_sign_type *pipe_check, int *i);
int	check_for_dbpipe_dbamper(char *input);

char	*trim_str(char *input, t_sign_type *sign_type, int *i, int status)
{
	char	*formated;
	int		save;

	save = *i;
	if (status == 1)
	{
		while (input[(*i)] && !ft_strnstr(input + *i, "||", 2) && input[(*i)] != '&')
		{
			if (input[(*i)] == D_QUOTES)
				(*i) += quote_ignore(input + (*i), D_QUOTES);
			else if (input[(*i)] == S_QUOTES)
				(*i) += quote_ignore(input + (*i), S_QUOTES);
			else if (input[(*i)] == '(')
				(*i) += parenthesis_ignore(input + (*i));
			(*i)++;
		}
	}
	else
	{
		while (input[(*i)] && input[(*i)] != '|' && input[(*i)] != '&')
		{
			if (input[(*i)] == D_QUOTES)
				(*i) += quote_ignore(input + (*i), D_QUOTES);
			else if (input[(*i)] == S_QUOTES)
				(*i) += quote_ignore(input + (*i), S_QUOTES);
			else if (input[(*i)] == '(')
				(*i) += parenthesis_ignore(input + (*i));
			(*i)++;
		}
	}
	formated = ft_calloc(sizeof(char), (((*i) - save) + 1));
	if (!formated)
		return (NULL);
	define_pipe_type(input, sign_type, i);
	return (build_str(formated, input + save, status));
}

static char	*build_str(char *formated, char *input, int status)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	if (!input)
		return (NULL);
	if (status == 1)
	{
		while (input[i] && !ft_strnstr(input + i, "||", 2) && input[i] != '&')
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
	}
	else
	{
		while (input[i] && input[i] != '|' && input[i] != '&')
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

static void	define_pipe_type(char *input, t_sign_type *sign_type, int *i)
{
	if (!input[(*i)])
		*sign_type = N_PIPE;
	else if (input[(*i) + 1] && input[(*i) + 1] == '|')
		*sign_type = D_PIPE;
	else if (input[(*i)] && input[(*i)] == '|')
		*sign_type = S_PIPE;
	else if (input[(*i)] && input[(*i)] == '&')
		*sign_type = AMPER;
}

int	check_for_dbpipe_dbamper(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if ((input[i] == '|' && input[i + 1] == '|') || input[i] == '&')
			return (1);
		i++;
	}
	return(0);
}