/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:47:33 by ruiolive          #+#    #+#             */
/*   Updated: 2024/03/30 22:40:24 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parse_input(char *input, t_counter *count_struct, t_init *init)
{
	int	i;

	i = 0;
	count_struct->prnt = 0;
	if (!check_begin_case_parser(input, &i))
		return (0);
	if (!parser(input, &i, count_struct))
		return (heardoc_check(init, input, count_struct, i), 0);
	return (heardoc_check(init, input, count_struct, i));
}

int	check_begin_case_parser(char *input, int *i)
{
	int	checker;

	while (input[(*i)] && ft_strchr(" \t\n", input[(*i)]))
		(*i)++;
	if (!input[(*i)])
		return (0);
	if (input[(*i)] && input[(*i) + 1] && \
	input[(*i)] == '>' && input[(*i) + 1] == '|')
	{
		(*i) += 2;
		checker = check_cmd_aft(input + (*i));
		if (!checker)
			return (error_handler(ERROR_NEWLINE, "newline", NULL), 0);
		else if (checker == -1)
			return (err_hlr_2(ERR_STR, search_char(input + (*i)), NULL), 0);
		return (1);
	}
	else if (input[(*i)] && ft_strchr("&|", input[(*i)]))
		return (err_hlr_2(ERR_STR, search_char(input + (*i)), NULL), 0);
	else if (signs_case(input + (*i)))
		return (err_hlr_2(ERR_STR, signs_case(input + (*i)), NULL), 0);
	if (!check_cmd_aft(input + (*i)))
		return (0);
	return (1);
}

int	parser(char *input, int *i, t_counter *count_struct)
{
	int	status_parenthesis;
	int	status_signs;
	int	status_quotes;

	while (input[(*i)])
	{
		status_quotes = quotes_parser(input, i);
		if (!status_quotes)
			return (0);
		status_parenthesis = parenthesis_parser(input, i, count_struct);
		if (!status_parenthesis)
			return (0);
		status_signs = signs_parser(input, i);
		if (!status_signs)
			return (0);
		else if (status_signs == 2)
			(*i)++;
	}
	return (1);
}
