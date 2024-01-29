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

#include "../includes/minishell.h"

static char	*build_str(char *formated, char *input);
static void	double_quotes_add(char **formated, char *input, int *i, int *x);
static void	single_quotes_add(char **formated, char *input, int *i, int *x);

char	*trim_str(char *input, t_type_pipe *pipe_check, int *i)
{
	char	*formated;
	int		save;

	save = *i;
	while (input[(*i)] && input[(*i)] != '|')
	{
		if (input[(*i)] == D_QUOTES)
			(*i) += quotes_check(input + (*i), D_QUOTES);
		else if (input[(*i)] == S_QUOTES)
			(*i) += quotes_check(input + (*i), S_QUOTES);
		else
			(*i)++;
	}
	formated = ft_calloc(sizeof(char), (((*i) - save) + 1));
	if (!formated)
		return (NULL);
	if (!input[(*i)])
		*pipe_check = N_PIPE;
	else if (input[(*i) + 1] && input[(*i) + 1] == '|')
		*pipe_check = D_PIPE;
	else if (input[(*i)] && input[(*i)] == '|')
		*pipe_check = S_PIPE;
	return (build_str(formated, input + save));
}

int	quotes_check(char *input, char c)
{
	int	i;

	i = 1;
	while (input[i] && input[i] != c)
		i++;
	return (i + 1);
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
	(*formated)[(*x)] = input[(*i)++];
	while (input[(*i)] && input[(*i)] != D_QUOTES)
	{
		(*formated)[(*x)] = input[(*i)];
		(*x)++;
		(*i)++;
	}
	(*formated)[(*x)] = input[(*i)++];
}

static void	single_quotes_add(char **formated, char *input, int *i, int *x)
{
	(*formated)[(*x)] = input[(*i)++];
	while (input[(*i)] && input[(*i)] != S_QUOTES)
	{
		(*formated)[(*x)] = input[(*i)];
		(*x)++;
		(*i)++;
	}
	(*formated)[(*x)] = input[(*i)++];
}
