/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars_parsers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:12:35 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/22 16:17:50 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int check_for_command(char *input);
static int	quotes_check(char *input, char c);
static int signs_check(char *input, char sign, char *ptr);

void check_unfinished_quotes(char *input)
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
					error_handler(ERROR_UNFINISHED_QUOTE, input, NULL);
				i++;
			}
		}
		i++;
	}
}

void	wrong_specialch_syntax(char *input)
{
    int			i;

    i = 0;
    while (input[i])
    {
		if (input[i] == D_QUOTES)
			i += quotes_check(input + i, D_QUOTES);
		else if (input[i] == S_QUOTES)
			i += quotes_check(input + i, S_QUOTES);
		else if (input[i] == '|')
			i += signs_check(input + i, '|', input);
		else if (input[i] == '&')
			i += signs_check(input + i, '&', input);
		else if (input[i] == '>')
			i += signs_check(input + i, '>', input);
		else if (input[i] == '<')
			i += signs_check(input + i, '<', input);
		else if (input[i] == '\\' || input[i] == ';')
			error_handler(ERROR_SPECIAL_CHAR, input, NULL);
		else
			i++;
    }
}

static int check_for_command(char *input)
{
	int	i;

	i = 0;
	
	while (input[i] == ' ' && input[i])
		i++;
	if (input[i] == '|' || input[i] == '&' \
		|| input[i] == '<' || input[i] == '>')
		return (0);
	return (1);
}
static int	quotes_check(char *input, char c)
{
	int	i;

	i = 1;
	while (input[i] && input[i] != c)	
		i++;
	return (i + 1);
}

static int signs_check(char *input, char sign, char *ptr)
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
	if (i > 2 || !check_for_command(input + i))
		error_handler(ERROR_SPECIAL_CHAR, ptr, NULL);
	return (i);
}
