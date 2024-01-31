/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:12:35 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/31 11:17:08 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_pipe_amper_next(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] == ' ')
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
	while (i >= 0 && input[i] == ' ')
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

int	check_for_command(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] == ' ')
		i++;
	if (!input[i] || (input[i] && ft_strchr("<>&|", input[i])))
		return (0);
	return (1);
}

int	pipe_count(char *input, int *i)
{
	int	x;

	x = *i;
	while (input[++(*i)] == '|')
			;
	if ((*i) - x > 2 || !check_pipe_amper_next(input + (*i)))
		return (0);
	return (1);
}

int	amper_count(char *input, int *i)
{
	int	x;

	x = *i;
	while (input[++(*i)] == '&')
			;
	if ((*i) - x != 2 || !check_pipe_amper_next(input + (*i)))
		return (0);
	return (1);
}
