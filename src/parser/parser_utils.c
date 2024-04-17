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

#include "../../includes/minishell.h"

int	check_cmd_end(char *input)
{
	int	i;

	i = 0;
	while (input[i] && ft_strchr(" \t\n", input[i]))
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
	while (i >= 0 && ft_strchr(" \t\n", input[i]))
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

int	check_cmd_aft(char *input)
{
	int	i;

	i = 0;
	while (input[i] && ft_strchr(" \t\n", input[i]))
		i++;
	if (!input[i])
		return (0);
	else if (input[i] && ft_strchr("<>&|()", input[i]))
		return (-1);
	return (1);
}

int	pipe_count(char *input, int *i)
{
	int	x;
	int	checker;

	checker = 0;
	x = *i;
	while (input[++x] == '|')
		;
	if ((x - (*i)) > 2)
		return (-1);
	checker = check_cmd_end(input + x);
	if (checker == 0 && x - (*i) == 1)
		return (-2);
	else if (checker == 0)
		return (-1);
	(*i) = x;
	return (1);
}

int	amper_count(char *input, int *i)
{
	int	x;
	int	checker;

	checker = 0;
	x = *i;
	while (input[++x] == '&')
		;
	if (x - (*i) > 2)
		return (-1);
	else if (x - (*i) == 1)
		return (-3);
	checker = check_cmd_end(input + x);
	if (checker == 0 && x - (*i) == 1)
		return (-2);
	else if (checker == 0)
		return (-1);
	(*i) = x;
	return (1);
}
