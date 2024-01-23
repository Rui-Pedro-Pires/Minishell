/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:47:33 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/23 16:37:50 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_input(char *input)
{
	int	i;

	i = 0;
	while (input[i] && (input[i] == ' ' \
	|| input[i] == '\t' || input[i] == '\n'))
		i++;
	if (!input[i])
	{
		error_handler(ERROR_WRONG_INPUT, input, NULL);
		return (0);
	}
	if (input[i] && (input[i] == '|' || input[i] == '<' \
	|| input[i] == '>' || input[i] == '&'))
	{
		error_handler(ERROR_WRONG_INPUT, input, NULL);
		return (0);
	}
	return (1);
}

int	check_unfinished_quotes(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!check_input(input))
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
					error_handler(ERROR_UNFINISHED_QUOTE, input, NULL), 0);
				i++;
			}
		}
		i++;
	}
	return (1);
}
