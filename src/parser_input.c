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

int	quotes_parser(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!input || !(*input))
		return (0);
	while (input[i] != '\0')
	{
		if (input[i] == D_QUOTES || input[i] == S_QUOTES)
		{
			j = i;
			i++;
			while (input[i] != input[j])
			{
				if (input[i] == '\0')
					return (\
					error_handler(ERROR_UNFINISHED_QUOTE, &input[j], NULL), 0);
				i++;
			}
		}
		i++;
	}
	return (1);
}

int	signs_parser(char *input, int *i, t_counter *count_struct)
{
	char	*errorch;
	int		checker;

	errorch = NULL;
	checker = 0;
	while (input[(*i)])
	{
		if (input[(*i)] == D_QUOTES)
			(*i) += quotes_check(input + (*i), D_QUOTES);
		else if (input[(*i)] == S_QUOTES)
			(*i) += quotes_check(input + (*i), S_QUOTES);
		else if (ft_strchr("<>&|", input[(*i)]))
		{
			checker = check_signs(input, i, &errorch);
			if (!checker)
				return (error_handler(ERROR_NEWLINE, "newline", NULL), 0);
			else if (checker == -1)
				return (err_hlr_2(ERR_STR, errorch, NULL), 0);
		}
		else if (ft_strchr("\\;", input[(*i)]))
			return (error_handler(ERROR_SPECIAL_CHAR, &input[(*i)], NULL), 0);
		else if (input[(*i)] == '(')
		{
			count_struct->prnt++;
			if (!check_for_error_bf_parenthesis(input, (*i)))
				return (err_hlr_2(ERR_STR, "(", NULL), 0);
			if (count_struct->prnt == 0 \
			&& !check_valid_parenthesis(input + (*i)))
				return (err_hlr_2(ERR_STR, ")", NULL), 0);
			(*i)++;
		}
		else if (input[(*i)] == ')')
		{
			count_struct->prnt--;
			if (count_struct->prnt < 0)
				return (err_hlr_2(ERR_STR, ")", NULL), 0);
			if (!check_for_error_af_parenthesis(input, (*i)))
				return (err_hlr_2(ERR_STR_FREE, string_error(input + (*i) + 1), NULL), 0);
			(*i)++;
		}
		else
			(*i)++;
	}
	return (1);
}

int	check_begin_case(char *input, int *i)
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

int	parse_input(char *input, t_counter *count_struct, char ***heardoc_read)
{
	int	i;

	i = 0;
	count_struct->prnt = 0;
	if (!quotes_parser(input))
		return (0);
	if (!check_begin_case(input, &i))
		return (0);
	if (!signs_parser(input, &i, count_struct))
		return (heardoc_check(heardoc_read, input, count_struct, i), 0);
	heardoc_check(heardoc_read, input, count_struct, i);
	return (1);
}

int	parenthesis_checker(char *input, t_counter *count_struct)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == D_QUOTES)
			i += quotes_check(input + i, D_QUOTES);
		else if (input[i] == S_QUOTES)
			i += quotes_check(input + i, S_QUOTES);
		if (input[i] == '(')
		{
			if (!check_for_error_bf_parenthesis(input, i))
				return (err_hlr_2(ERR_STR, "(", NULL), 0);
			if (count_struct->prnt == 0 \
			&& !check_valid_parenthesis(input + i))
				return (err_hlr_2(ERR_STR, ")", NULL), 0);
		}
		else if (input[i] == ')')
		{
			if (!check_for_error_af_parenthesis(input, i))
				return (err_hlr_2(ERR_STR_FREE, string_error(input + i + 1), NULL), 0);
		}
		i++;
	}
	return (1);
}
