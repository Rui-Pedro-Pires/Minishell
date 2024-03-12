/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_str_list_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive  <ruiolive@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:07:14 by ruiolive          #+#    #+#             */
/*   Updated: 2024/03/12 11:07:14 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	double_quotes_add(char **formated, char *input, int *i, int *x)
{
	(*formated)[(*x)++] = input[(*i)++];
	while (input[(*i)] && input[(*i)] != D_QUOTES)
	{
		(*formated)[(*x)] = input[(*i)];
		(*x)++;
		(*i)++;
	}
	(*formated)[(*x)++] = input[(*i)++];
}

void	single_quotes_add(char **formated, char *input, int *i, int *x)
{
	(*formated)[(*x)++] = input[(*i)++];
	while (input[(*i)] && input[(*i)] != S_QUOTES)
	{
		(*formated)[(*x)] = input[(*i)];
		(*x)++;
		(*i)++;
	}
	(*formated)[(*x)++] = input[(*i)++];
}

int	parenthesis_ignore(char *input)
{
	int	i;
	int	parenthesis_num;

	parenthesis_num = 1;
	i = 1;
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

void	parenthesis_add(char **formated, char *input, int *i, int *x)
{
	int	parenthesis_num;

	parenthesis_num = 0;
	while (input[(*i)])
	{
		if (input[(*i)] == '(')
			parenthesis_num++;
		else if (input[(*i)] == ')')
			parenthesis_num--;
		if (parenthesis_num == 0)
			break ;
		(*formated)[(*x)] = input[(*i)];
		(*x)++;
		(*i)++;
	}
}
