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
	if (input[(*i)] && input[(*i)] == '|')
		return (pipe_checker(input, i, myChar));
	else if (input[(*i)] && input[(*i)] == '&')
		return (amper_checker(input, i, myChar));
	else if (input[(*i)] && input[(*i)] == '>')
		return (major_checker(input, i, myChar));
	else if (input[(*i)] && input[(*i)] == '<')
		return (minor_checker(input, i, myChar));
	return (1);
}

int	major_sig_count(char *input, int *i)
{
	int	x;

	x = *i;
	while (input[++ (*i)] == '>')
			;
	if ( (*i) - x < 2 && input[(*i)] == '|' && check_for_command_after(input + ((*i) + 1)))
		return (1);
	if ( (*i) - x > 2)
		return (0);
	if (!check_for_command_after(input +  (*i)))
		return (-1);
	return (1);
}

int	minor_sig_count(char *input, int *i)
{
	int	x;

	x = *i;
	while (input[++ (*i)] == '<')
			;
	if ( (*i)- x > 2)
		return (0);
	if (!check_for_command_after(input +  (*i)))
		return (-1);
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
