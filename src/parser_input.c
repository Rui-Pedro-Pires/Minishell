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

int	signs_parser(char *input, int i)
{
	char *errorChars;
	int	checker;

	errorChars = NULL;
	checker = 0;
	while (input[i])
	{
		if (input[i] == D_QUOTES)
			i += quotes_check(input + i, D_QUOTES);
		else if (input[i] == S_QUOTES)
			i += quotes_check(input + i, S_QUOTES);
		else if (ft_strchr("<>&|", input[i]))
		{
			checker = check_signs(input, &i, &errorChars);
			if (!checker)
				return (error_handler(ERROR_NEWLINE, "newline", NULL), 0);
			else if (checker == -1)
				return (error_handler_2(ERROR_STRING_TYPE, errorChars, NULL), 0);
		}
		else if (ft_strchr("\\;", input[i]))
			return (error_handler(ERROR_SPECIAL_CHAR, &input[i], NULL), 0);
		else
			i++;
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
		checker = check_for_command_after(input + (*i));
		if (!checker)
			return (error_handler(ERROR_NEWLINE, "newline", NULL), 0);
		else if (checker == -1)
			return (error_handler_2(ERROR_STRING_TYPE, search_char(input + (*i)), NULL), 0);
		return (1);
	}
	else if (input[(*i)] && ft_strchr("&|", input[(*i)]))
		return (error_handler_2(ERROR_STRING_TYPE, search_char(input + (*i)), NULL), 0);
	else if (signs_case(input + (*i)))
		return (error_handler_2(ERROR_STRING_TYPE, signs_case(input + (*i)), NULL), 0);
	if (!check_for_command_after(input + (*i)))
		return (0);
	return (1);
}

int	parse_input(char *input)
{
	int	i;

	i = 0;
	if (!quotes_parser(input))
		return (0);
	if (!check_begin_case(input, &i))
		return (0);
	if (!signs_parser(input, i))
		return (0);
	return (1);
}
