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

int	check_signs(char *input, int *i, char *myChar)
{
	if (input[(*i)] == '|')
	{
		if (!pipe_count(input, i))
			return (*myChar='|', 0);
	}
	else if (input[(*i)] == '&')
	{
		if (!amper_count(input, i))
			return (*myChar='&', 0);
	}
	else if (input[(*i)] == '>')
	{
		if (!major_sig_count(input, i))
			return (*myChar='>', 0);
	}
	else if (input[(*i)] == '<')
	{
		if (!minor_sig_count(input, i))
			return (*myChar='<', 0);
	}
	return (1);
}

int	major_sig_count(char *input, int *i)
{
	int	x;

	x = *i;
	while (input[++(*i)] == '>')
			;
	if ((*i) - x < 2 && input[(*i)] == '|' && check_for_command_after(input + ((*i) + 1)))
		return (1);
	if ((*i) - x > 2 || !check_for_command_after(input + (*i)))
		return (0);
	return (1);
}

int	minor_sig_count(char *input, int *i)
{
	int	x;

	x = *i;
	while (input[++(*i)] == '<')
			;
	if ((*i) - x > 2 || !check_for_command_after(input + (*i)))
		return (0);
	return (1);
}
