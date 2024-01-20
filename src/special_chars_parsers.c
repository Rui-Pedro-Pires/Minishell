/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars_parsers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:12:35 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/19 12:48:37 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_handler(int type)
{
	if (type == 1)
		printf("ERROR\n");
}

int signs_check(char *input, char sign)
{
	int	i;

	i = 0;
	if (sign == '>')
		while (input[++i] == '>');
	else if (sign == '<')
		while (input[++i] == '<');
	else if (sign == '|')
		while (input[++i] == '|');
	else if (sign == '&')
		while (input[++i] == '&');
	if (i > 2)
		error_handler(1);
	return (i);
}

void	wrong_specialch_syntax(char *input)
{
    int	i;

    i = 0;
    while (input[i])
    {
		if (input[i] == '|')
			i += signs_check(input + i, '|');
		else if (input[i] == '&')
			i += signs_check(input + i, '&');
		else if (input[i] == '>')
			i += signs_check(input + i, '>');
		else if (input[i] == '<')
			i += signs_check(input + i, '<');
		else if (input[i] == '\\' || input[i] == ';')
			error_handler(1);
		else
			i++;
    }
}