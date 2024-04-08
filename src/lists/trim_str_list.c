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

static void	loop_to_trim_case_status1(char *input, int *i);
static void	loop_to_trim_case_status_not_1(char *input, int *i);

char	*trim_str(char *input, t_sign_type *sign_type, int *i, int status)
{
	char	*formated;
	int		save;

	save = *i;
	if (status == 1)
		loop_to_trim_case_status1(input, i);
	else
		loop_to_trim_case_status_not_1(input, i);
	formated = ft_calloc(sizeof(char), (((*i) - save) + 1));
	if (!formated)
		return (NULL);
	define_pipe_type(input, sign_type, i);
	return (build_str(formated, input + save, status));
}

static void	loop_to_trim_case_status1(char *input, int *i)
{
	while (input[(*i)] && !ft_strnstr(input + *i, "||", 2) \
	&& input[(*i)] != '&')
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

static void	loop_to_trim_case_status_not_1(char *input, int *i)
{
	while (input[(*i)] && input[(*i)] != '|' && input[(*i)] != '&')
	{
		if (input[(*i)] == D_QUOTES)
			(*i) += quote_ignore(input + (*i), D_QUOTES);
		else if (input[(*i)] == S_QUOTES)
			(*i) += quote_ignore(input + (*i), S_QUOTES);
		else if (input[(*i)] == '(')
			(*i) += parenthesis_ignore(input + (*i));
		if (ft_strnstr(input + (*i), ">|", 2))
			(*i)++;
		(*i)++;
	}
}
