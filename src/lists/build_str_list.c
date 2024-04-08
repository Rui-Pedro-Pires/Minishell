/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_str_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive  <ruiolive@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:09:17 by ruiolive          #+#    #+#             */
/*   Updated: 2024/03/12 11:09:17 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	loop_to_build_case_status1(char *input, char *formated, \
int *i, int *x);
static void	loop_to_build_case_status_not_1(char *input, char *formated, \
int *i, int *x);

char	*build_str(char *formated, char *input, int status)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	if (!input)
		return (NULL);
	if (status == 1)
		loop_to_build_case_status1(input, formated, &i, &x);
	else
		loop_to_build_case_status_not_1(input, formated, &i, &x);
	return (formated);
}

static void	loop_to_build_case_status1(char *input, char *formated, \
int *i, int *x)
{
	while (input[(*i)] && !ft_strnstr(input + (*i), "||", 2) \
	&& input[(*i)] != '&')
	{
		if (input[(*i)] == D_QUOTES)
			double_quotes_add(&formated, input, i, x);
		else if (input[(*i)] == S_QUOTES)
			single_quotes_add(&formated, input, i, x);
		else if (input[(*i)] == '(')
			parenthesis_add(&formated, input, i, x);
		else
		{
			formated[(*x)] = input[(*i)];
			(*x)++;
			(*i)++;
		}
	}
}

static void	loop_to_build_case_status_not_1(char *input, char *formated, \
int *i, int *x)
{
	while (input[(*i)] && input[(*i)] != '|' && input[(*i)] != '&')
	{
		if (input[(*i)] == D_QUOTES)
			double_quotes_add(&formated, input, i, x);
		else if (input[(*i)] == S_QUOTES)
			single_quotes_add(&formated, input, i, x);
		else if (input[(*i)] == '(')
			parenthesis_add(&formated, input, i, x);
		else if (ft_strnstr(input + (*i), ">|", 2))
		{
			formated[(*x)++] = input[(*i)++];
			formated[(*x)++] = input[(*i)++];
		}
		else
		{
			formated[(*x)] = input[(*i)];
			(*x)++;
			(*i)++;
		}
	}
}
