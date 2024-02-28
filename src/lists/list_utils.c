/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:43:48 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/25 12:02:25 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_pipes	*find_last_node(t_pipes *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
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
