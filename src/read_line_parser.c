/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:14:26 by ruiolive          #+#    #+#             */
/*   Updated: 2024/02/01 10:22:46 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_parenthesis(char *input, int *parenthesis, int *check_empty, int *i)
{
	if (!input || !input[(*i)])
		return (1);
	while (input[(*i)])
	{
		if (!ft_strchr("|<>&()", input[(*i)]))
			(*check_empty) = 0;
		if (input[(*i)] == D_QUOTES)
			(*i) += quotes_check(input + (*i), D_QUOTES);
		else if (input[(*i)] == S_QUOTES)
			(*i) += quotes_check(input + (*i), S_QUOTES);
		if (input[(*i)] && (input[(*i)] == ')' || input[(*i)] == '('))
		{
			if (!parenthesis_parser(input, (*i), parenthesis, check_empty))
				return (0);
		}
		if ((input[(*i)] && input[(*i)] == ')' \
		&& (*check_empty) == 1) || (*parenthesis) < 0)
			return (error_handler(ERROR_SPECIAL_CHAR, &")", NULL), 0);
		(*i)++;
	}
	return (1);
}

int	parenthesis_parser(char *input, int i, int *parenthesis, int *check_empty)
{
	if (input[i] && input[i] == '(')
	{
		if (!check_separator_before(input, i))
			return (error_handler(ERROR_NEWLINE, &"newline", NULL), 0);
		(*parenthesis)++;
		(*check_empty) = 1;
	}
	else if (input[i] && input[i] == ')' && (*check_empty) == 0)
	{
		if (!check_separator_after(input, i))
			return (error_handler(ERROR_NEWLINE, &"newline", NULL), 0);
		(*parenthesis)--;
	}
	return (1);
}

int	check_separator_before(char *input, int i)
{
	if (i == 0)
		return (1);
	i--;
	while (i >= 0 && input[i] == ' ')
		i--;
	if (input[i] && ft_strchr("|&<>()", input[i]))
		return (1);
	return (0);
}

int	check_separator_after(char *input, int i)
{
	if (!input[i])
		return (1);
	i++;
	while (input[i] && input[i] == ' ')
		i++;
	if (input[i] && ft_strchr("|&<>", input[i]))
		return (1);
	else if (!input[i])
		return (1);
	return (0);
}

int	unfinished_command_line(char *input)
{
	int	i;

	i = 0;
	if (!input || !(*input))
		return (0);
	while (input[i + 1])
		i++;
	while (i >= 0 && input[i] == ' ')
		i--;
	if (input[i] == '|' || input[i] == '&')
		return (1);
	return (0);
}
