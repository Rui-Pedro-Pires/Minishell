/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_signs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:05:34 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/31 14:48:16 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_signs(char *input, int *i, char **myChar)
{
	int	x;

	x = *i;
	if (input[x] == '|')
		return (pipe_checker(input, &x, myChar));
	else if (input[x] == '&')
		return (amper_checker(input, &x, myChar));
	else if (input[x] == '>')
		return (major_checker(input, &x, myChar));
	else if (input[x] == '<')
		return (minor_checker(input, &x, myChar));
	(*i) = x;
	return (1);
}

int	major_sig_count(char *input, int *i)
{
	int	x;

	x = *i;
	while (input[++x] == '>')
			;
	if (x - (*i) < 2 && input[(*i)] == '|' && check_for_command_after(input + (x + 1)))
		return (1);
	if (x - (*i) > 2)
		return (0);
	if (!check_for_command_after(input + x))
		return (-1);
	(*i) = x;
	return (1);
}

int	minor_sig_count(char *input, int *i)
{
	int	x;

	x = *i;
	while (input[++x] == '<')
			;
	if (x - (*i) > 2)
		return (0);
	if (!check_for_command_after(input + x))
		return (-1);
	(*i) = x;
	return (1);
}

char	*signs_case(char *input)
{
	int	i;

	i = 0;
	if (input[i] == '>')
	{
		i++;
		if (input[i] && input[i] == '>')
			i++;
		while (input[i] && input[i] == ' ')
			i++;
		if (input[i] && ft_strchr("|&<>", input[i]))
			return (search_char(input + i));
	}
	if (input[i] == '<')
	{
		i++;
		if (input[i] && input[i] == '<')
			i++;
		while (input[i] && input[i] == ' ')
			i++;
		if (input[i] && ft_strchr("|&<>", input[i]))
			return (search_char(input + i));
	}
	return (NULL);
}
