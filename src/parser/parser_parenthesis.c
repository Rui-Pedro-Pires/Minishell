/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_parenthesis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive  <ruiolive@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:55:09 by ruiolive          #+#    #+#             */
/*   Updated: 2024/02/14 13:55:09 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_parenthesis(char *input, t_counter *cnt)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == D_QUOTES)
			i += quote_ignore(input + i, D_QUOTES);
		else if (input[i] == S_QUOTES)
			i += quote_ignore(input + i, S_QUOTES);
		if (input[i] && input[i] == '(')
			cnt->prnt++;
		else if (input[i] && input[i] == ')')
			cnt->prnt--;
		if (cnt->prnt < 0)
			return (1);
		i++;
	}
	return (1);
}

int	check_for_error_bf_parenthesis(char *input, int i)
{
	if (i == 0)
		return (1);
	i--;
	while (i > 0 && ft_strchr(" \t\n", input[i]))
		i--;
	if (input[i] && (ft_strchr("&() \t\n", input[i]) \
	|| ft_strnstr(input + (i - 1), "||", 2)))
		return (1);
	return (0);
}

int	check_for_error_af_parenthesis(char *input, int i)
{
	i++;
	if (!input[i])
		return (1);
	while (input[i] && ft_strchr(" \t\n", input[i]))
		i++;
	if (!input[i])
		return (1);
	if (input[i] && (ft_strchr("&) \t\n", input[i]) \
	|| ft_strnstr(input + i, "||", 2)))
		return (1);
	return (0);
}

int	check_valid_parenthesis(char *input)
{
	int		i;
	int		correct_parenthesis;
	bool	command1;
	bool	command2;
	bool	dpipe_damper;

	i = 1;
	correct_parenthesis = search_correct_parenthesis(input);
	command1 = search_command(input, &i, correct_parenthesis);
	dpipe_damper = search_dpipe_or_damper(input, &i, correct_parenthesis);
	command2 = search_command(input, &i, correct_parenthesis);
	if (!input[correct_parenthesis])
		return (1);
	correct_parenthesis--;
	while (correct_parenthesis >= 0 && input[correct_parenthesis] == ' ')
		correct_parenthesis--;
	if (ft_strchr("|&><", input[correct_parenthesis]))
		return (0);
	if (command1 && command2 && dpipe_damper)
		return (1);
	return (0);
}
