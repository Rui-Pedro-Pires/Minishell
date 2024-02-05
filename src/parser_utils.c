/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:12:35 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/31 14:48:16 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_pipe_amper_next(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] == ' ')
		i++;
	if (input[i] && ft_strchr("&|", input[i]))
		return (0);
	return (1);
}

int	check_end(char *input)
{
	int	i;

	i = 0;
	while (input[i + 1])
		i++;
	while (i >= 0 && input[i] == ' ')
		i--;
	if (!ft_strchr("<>&|", input[i]))
		return (1);
	while (input[i])
	{
		if (ft_strchr("<>", input[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_for_command_after(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] == ' ')
		i++;
	if (!input[i])
		return (-1);
	else if (input[i] && ft_strchr("<>&|()", input[i]))
		return (-2);
	return (1);
}

int	pipe_count(char *input, int *i)
{
	int	x;

	x = *i;
	while (input[++x] == '|')
			;
	if (x - (*i) > 3 || !check_pipe_amper_next(input + x))
		return (-2);
	if (x - (*i) > 2 || !check_pipe_amper_next(input + x))
		return (-1);
	(*i) = x;
	return (1);
}

int	amper_count(char *input, int *i)
{
	int	x;

	x = *i;
	while (input[++x] == '&')
			;
	if (x - (*i) > 3 || !check_pipe_amper_next(input + x))
		return (-2);
	if (x - (*i) != 2 || !check_pipe_amper_next(input + x))
		return (-1);
	(*i) = x;
	return (1);
}

char	*search_char(char  *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] == ' ')
		i++;
	if (input[i] && input[i] == '>')
		return (">");
	if (input[i] && input[i] == '<')
		return ("<");
	if (input[i] && input[i] == '|')
		return ("|");
	if (input[i] && input[i] == '&')
		return ("&");
	if (input[i] && input[i] == '(')
		return ("(");
	if (input[i] && input[i] == ')')
		return (")");
	return (0);
}
