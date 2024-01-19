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

int pipe_check(char *input)
{
	int	i;

	i = 0;
	while (input[i] == '|')
		i++;
	if (i > 2)
	{
		//error_handler();
		printf("ERROR");
		exit(1);
	}
	return (i);
}

int ampersand_check(char *input)
{
	int	i;

	i = 0;
	while (input[i] == '&')
		i++;
	if (i > 2)
	{
		//error_handler();
		printf("ERROR");
		exit(1);
	}
	return (i);
}

int signs_check(char *input, char sign)
{
	int	i;

	i = 0;
	if (sign == '>')
	{
		while (input[i] == '>')
			i++;
	}
	else if (sign == '<')
	{
		while (input[i] == '<')
			i++;
	}
	if (i > 2)
	{
		//error_handler();
		printf("ERROR");
		exit(1);
	}
	return (i);
}

void	wrong_specialch_syntax(char *input)
{
    int	i;

    i = 0;
    while (input[i])
    {
		if (input[i] == '|')
			i += pipe_check(input + i);
		else if (input[i] == '&')
			i += ampersand_check(input + i);
		else if (input[i] == '>')
			i += signs_check(input + i, '>');
		else if (input[i] == '<')
			i += signs_check(input + i, '<');
		else if (input[i] == '\\' || input[i] == ';')
		{
			//error_handler();
			printf("ERROR");
			exit(1);
		}
		i++;
    }
}