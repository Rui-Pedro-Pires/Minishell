/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:47:33 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/31 15:19:37 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	parse_input(char *input, t_counter *count_struct, char ***heardoc_read)
{
	int	i;

	i = 0;
	count_struct->i = 0;
	count_struct->counter = 0;
	count_struct->prnt = 0;
	if (!check_begin_case_parser(input, &i))
		return (0);
	if (!parser(input, &i, count_struct))
		return (heardoc_check(heardoc_read, input, count_struct, i), 0);
	heardoc_check(heardoc_read, input, count_struct, i);
	return (1);
}

int	check_begin_case_parser(char *input, int *i)
{
	int	checker;

	while (input[(*i)] && (input[(*i)] == ' ' \
	|| input[(*i)] == '\t' || input[(*i)] == '\n'))
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

int quotes_parser(char *input, int *i)
{
	int	status;
	if (input[(*i)] == D_QUOTES)
	{
		status = quote_check(input, i, D_QUOTES);
		if (status == 0)
			return (err_hlr_2(ERR_STR, "\"", NULL), 0);
	}
	else if (input[(*i)] == S_QUOTES)
	{
		status = quote_check(input, i, S_QUOTES);
		if (status == 0)
			return (err_hlr_2(ERR_STR, "\'", NULL), 0);
	}
	return (1);
}

int	parenthesis_parser(char *input, int *i, t_counter *count_struct)
{
	int	x;

	x = *i;
	if (input[x] == '(')
	{
		count_struct->prnt++;
		if (!check_for_error_bf_parenthesis(input, x))
			return (err_hlr_2(ERR_STR, "(", NULL), 0);
		if (count_struct->prnt == 0 \
		&& !check_valid_parenthesis(input + x))
			return (err_hlr_2(ERR_STR, ")", NULL), 0);
	}
	else if (input[x] == ')')
	{
		count_struct->prnt--;
		if (count_struct->prnt < 0)
			return (err_hlr_2(ERR_STR, ")", NULL), 0);
		if (!check_for_error_af_parenthesis(input, x))
			return (err_hlr_2(ERR_STR_FREE, string_error(input + x + 1), NULL), 0);
	}
	return (1);
}

int	signs_parser(char *input, int *i)
{
	char	*errorch;
	int		checker;

	errorch = NULL;
	checker = 0;
	if (ft_strchr("<>&|", input[(*i)]))
	 {
	 	checker = check_signs(input, i, &errorch);
	 	if (!checker)
	 		return (error_handler(ERROR_NEWLINE, "newline", NULL), 0);
	 	else if (checker == -1)
	 		return (err_hlr_2(ERR_STR, errorch, NULL), 0);
		return (1);
	 }
	 else if (ft_strchr("\\;", input[(*i)]))
	 	return (error_handler(ERROR_SPECIAL_CHAR, &input[(*i)], NULL), 0);
	return (2);
}

int	quote_ignore(char *input, char c)
{
	int	i;

	i = 1;
	while (input[i] && input[i] != c)
		i++;
	return (i);
}

int	quote_check(char *input, int *i, char c)
{
	int	x;

	x = (*i) + 1;
	if (!input[x])
		return (0);
	while (input[x] && input[x] != c)
		x++;
	if (!input[x])
		return (0);
	*i = x;
	return (1);
}
