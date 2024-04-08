/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_diff_signs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive  <ruiolive@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:41:07 by ruiolive          #+#    #+#             */
/*   Updated: 2024/02/05 15:41:07 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_checker(char *input, int *i, char **myChar)
{
	int	checker;

	checker = pipe_count(input, i);
	if (checker == -1)
	{
		*i += 2;
		*myChar = search_char(input + (*i));
		return (-1);
	}
	else if (checker == -2)
	{
		*i += 1;
		*myChar = search_char(input + (*i));
		return (-1);
	}
	return (1);
}

int	amper_checker(char *input, int *i, char **myChar)
{
	int	checker;

	checker = amper_count(input, i);
	if (checker == -1)
	{
		*i += 2;
		*myChar = search_char(input + (*i));
		return (-1);
	}
	else if (checker == -2)
	{
		*i += 1;
		*myChar = search_char(input + (*i));
		return (-1);
	}
	else if (checker == -3)
	{
		*myChar = search_char(input + (*i));
		return (-1);
	}
	return (1);
}

int	major_checker(char *input, int *i, char **myChar)
{
	int	checker;

	checker = major_sig_count(input, i);
	if (checker == -1)
	{
		*i += 2;
		*myChar = search_char(input + (*i));
		return (-1);
	}
	else if (checker == -2)
	{
		*i += 1;
		*myChar = search_char(input + (*i));
		return (-1);
	}
	else if (checker == 0)
		return (0);
	return (1);
}

int	minor_checker(char *input, int *i, char **myChar)
{
	int	checker;

	checker = minor_sig_count(input, i);
	if (checker == -1)
	{
		*i += 2;
		*myChar = search_char(input + (*i));
		return (-1);
	}
	else if (checker == -2)
	{
		*i += 1;
		*myChar = search_char(input + (*i));
		return (-1);
	}
	else if (checker == -3)
	{
		*i += 2;
		*myChar = "<>";
		return (-1);
	}
	else if (checker == 0)
		return (0);
	return (1);
}
