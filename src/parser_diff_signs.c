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

#include "../includes/minishell.h"

int	pipe_checker(char *input, int *x, char **myChar)
{
	int	checker;

	checker = pipe_count(input, x);
	if (!checker)
	{
		*x += 2;
		*myChar = search_char(input + (*x));
		return (0);
	}
	else if (checker == -1)
		return (-1);
	return (1);
}

int	amper_checker(char *input, int *x, char **myChar)
{
	int	checker;

	checker = amper_count(input, x);
	if (!checker)
	{
		*x += 2;
		*myChar = search_char(input + (*x));
		return (0);
	}
	else if (checker == -1)
		return (-1);
	return (1);
}

int	major_checker(char *input, int *x, char **myChar)
{
	int	checker;

	checker = major_sig_count(input, x);
	if (!checker)
	{
		*x += 2;
		*myChar = search_char(input + (*x));
		return (0);
	}
	else if (checker == -1)
		return (-1);
	return (1);
}

int	minor_checker(char *input, int *x, char **myChar)
{
	int	checker;

	checker = minor_sig_count(input, x);
	if (!checker)
	{
		*x += 2;
		*myChar = search_char(input + (*x));
		return (0);
	}
	else if (checker == -1)
		return (-1);
	return (1);
}
