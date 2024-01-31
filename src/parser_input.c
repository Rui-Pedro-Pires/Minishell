/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:47:33 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/31 11:06:01 by ruiolive         ###   ########.fr       */
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
					error_handler(ERROR_UNFINISHED_QUOTE, input, NULL), 0); /*#TODO Add aspas to the error message*/
				i++;
			}
		}
		i++;
	}
	return (1);
}

int	signs_parser(char *input, int i)
{
	while (input[i])
	{
		if (input[i] == D_QUOTES)
			i += quotes_check(input + i, D_QUOTES);
		else if (input[i] == S_QUOTES)
			i += quotes_check(input + i, S_QUOTES);
		else if (ft_strchr("<>&|", input[i]))
		{
			if (!check_signs(input, &i))
				return (error_handler(ERROR_SPECIAL_CHAR, NULL, NULL), 0);
		}
		else if (ft_strchr("\\;", input[i]))
			return (error_handler(ERROR_SPECIAL_CHAR, &input[i], NULL), 0);
		else
			i++;
	}
	if (!check_end(input))
		return (error_handler(ERROR_SPECIAL_CHAR, NULL, NULL), 0);
	return (1);
}

int	check_begin_case(char *input, int *i)
{
	while (input[(*i)] && (input[(*i)] == ' ' \
	|| input[(*i)] == '\t' || input[(*i)] == '\n'))
		(*i)++;
	if (!input[(*i)])
		return (0);
	if (input[(*i)] && input[(*i) + 1] && \
	input[(*i)] == '>' && input[(*i) + 1] == '|')
	{
		(*i) += 2;
		if (!check_for_command(input + (*i)))
			return (0);
		return (1);
	}
	else if (input[(*i)] && ft_strchr("<>&|", input[(*i)]))
		return (0);
	if (!check_for_command(input + (*i)))
		return (0);
	return (1);
}
