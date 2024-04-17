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

#include "../../includes/minishell.h"

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

int	ft_return_check(char *input, int *i, int *x)
{
	int	checker;

	checker = check_cmd_aft(input + (*x));
	if (*x - (*i) == 1 && input[(*x)] == '>' && \
	!check_cmd_aft(input + ((*x) + 1)))
		return (0);
	if (*x - (*i) == 1 && input[(*x)] == '>' && \
	check_cmd_aft(input + ((*x) + 1)) == -1)
		return (-1);
	if (checker == 0)
		return (0);
	else if (checker == -1 && (*x) - (*i) == 1)
		return (-2);
	else if (checker == -1)
		return (-1);
	return (1);
}

char	*check_minor_case_special_error(char *input, int i)
{
	if (input[i] && ft_strchr(">", input[i]) && !check_cmd_aft(input + i + 1))
		return ("newline");
	if (input[i] && ft_strchr(">", input[i]) && ft_strchr("<", input[i + 1]) \
	&& input[i + 2] && ft_strchr(">", input[i + 2]))
		return ("<>");
	if (input[i] && ft_strchr(">", input[i]) && check_cmd_aft(input + i + 1))
		return (NULL);
	if (input[i] && input[i] == '<')
		i++;
	while (input[i] && ft_strchr(" \t\n", input[i]))
		i++;
	if (input[i] && ft_strchr("|&<", input[i]))
		return (search_char(input + i));
	return (NULL);
}
