/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_signs_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive  <ruiolive@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:27:05 by ruiolive          #+#    #+#             */
/*   Updated: 2024/02/28 10:27:05 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	major_sig_count(char *input, int *i)
{
	int	x;
	int	checker;

	x = *i;
	checker = 0;
	while (input[++x] == '>')
		;
	if (x - (*i) > 2)
		return (-1);
	if (x - (*i) < 2 && input[x] == '|' && check_cmd_aft(input + (x + 1)) == 1)
	{
		(*i) = x;
		return (1);
	}
	if (input[x] == '|')
		x++;
	checker = check_cmd_aft(input + x);
	if (checker == 0)
		return (0);
	else if (checker == -1 && x - (*i) == 1)
		return (-2);
	else if (checker == -1)
		return (-1);
	(*i) = x;
	return (1);
}

int	minor_sig_count(char *input, int *i)
{
	int	x;
	int	checker;

	x = *i + 1;
	checker = 0;
	while (input[x] && input[x] == '<')
		x++;
	if (x - (*i) == 3 && ft_strchr(">", input[x]))
		return (-3);
	if (x - (*i) > 2)
		return (-1);
	if (x - (*i) == 1 && input[(x)] == '>' && \
	check_cmd_aft(input + (x + 1)) == 1)
	{
		*i = x;
		return (1);
	}
	checker = ft_return_check(input, i, &x);
	if (checker != 1)
		return (checker);
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
		return (check_minor_case_special_error(input, i));
	}
	return (NULL);
}
