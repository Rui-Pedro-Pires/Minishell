/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive  <ruiolive@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:32:46 by ruiolive          #+#    #+#             */
/*   Updated: 2024/02/28 10:32:46 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	quotes_parser(char *input, int *i)
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
		if (!check_valid_parenthesis(input + x))
			return (err_hlr_2(ERR_STR, ")", NULL), 0);
	}
	else if (input[x] == ')')
	{
		count_struct->prnt--;
		if (count_struct->prnt < 0)
			return (err_hlr_2(ERR_STR, ")", NULL), 0);
		if (!check_for_error_af_parenthesis(input, x))
			return (err_hlr_2(ERR_STR_FREE, \
			string_error(input + x + 1), NULL), 0);
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
