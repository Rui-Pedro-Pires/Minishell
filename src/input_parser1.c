/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:47:33 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/30 09:30:34 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_input(char *input, int *i)
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
		if (!check_if_command_exits(input + (*i)))
			return (0);
		return (1);
	}
	else if (input[(*i)] && (input[(*i)] == '|' || input[(*i)] == '<' \
	|| input[(*i)] == '>' || input[(*i)] == '&'))
		return (0);
	return (1);
}

int	check_unfinished_quotes(char *input)
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
					error_handler(ERROR_UNFINISHED_QUOTE, input, NULL), 0);
				i++;
			}
		}
		i++;
	}
	return (1);
}

int	check_pipe_amper_next(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] == ' ')
		i++;
	if (input[i] && (input[i] == '&' || input[i] == '|'))
		return (0);
	return (1);
}

int	check_for_command(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ' && input[i])
		i++;
	if (input[i] && (input[i] == '<' || input[i] == '>' \
	|| input[i] == '&' || input[i] == '|'))
		return (0);
	return (1);
}

int	check_if_command_exits(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] == ' ')
		i++;
	if (!input[i])
		return (0);
	return (1);
}
