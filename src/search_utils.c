/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive  <ruiolive@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:12:47 by ruiolive          #+#    #+#             */
/*   Updated: 2024/02/14 13:12:47 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	search_command(char *input, int *i, int correct_parenthesis)
{
	while (input[(*i)] && *i <= correct_parenthesis)
	{
		if (ft_strchr("(", input[(*i)]))
		{
			(*i) = search_correct_parenthesis(input + (*i));
			return (true);
		}
		else if (!ft_strchr("|&<> ()", input[(*i)]))
			return (true);
		(*i)++;
	}
	return (false);
}

bool	search_dpipe_or_damper(char *input, int *i, int correct_parenthesis)
{
	while (input[(*i)] && *i <= correct_parenthesis)
	{
		if (ft_strnstr(input + (*i), "||", 2) \
		|| ft_strnstr(input + (*i), "&&", 2))
			return (true);
		(*i)++;
	}
	return (false);
}

int	search_correct_parenthesis(char *input)
{
	int	i;
	int	parenthesis_num;

	i = 1;
	parenthesis_num = 1;
	while (input[i])
	{
		if (input[i] == '(')
			parenthesis_num++;
		else if (input[i] == ')')
			parenthesis_num--;
		if (parenthesis_num == 0)
			break ;
		i++;
	}
	return (i);
}
