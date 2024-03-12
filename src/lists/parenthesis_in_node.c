/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_case.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive  <ruiolive@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:47:19 by ruiolive          #+#    #+#             */
/*   Updated: 2024/03/12 11:47:19 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	bet_parent_count(char *formated, int *x);
void		bet_parent_add(char *formated, char **bet_parent, int x, int i);

char	*create_str_bet_parent(char *formated)
{
	char	*formated_parenthesis;
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (formated[i] && formated[i] == ' ')
		i++;
	if (formated[i] != '(')
		return (NULL);
	i++;
	x = i;
	bet_parent_count(formated, &x);
	formated_parenthesis = ft_calloc(sizeof(char), x - i + 1);
	x = 0;
	bet_parent_add(formated, &formated_parenthesis, x, i);
	return (formated_parenthesis);
}

static void	bet_parent_count(char *formated, int	*x)
{
	int	parenthesis_num;

	parenthesis_num = 1;
	while (formated[(*x)])
	{
		if (formated[(*x)] == '(')
			parenthesis_num++;
		else if (formated[(*x)] == ')')
			parenthesis_num--;
		if (parenthesis_num == 0)
			break ;
		(*x)++;
	}
}

void	bet_parent_add(char *formated, char **bet_parent, int x, int i)
{
	int	parenthesis_num;

	parenthesis_num = 1;
	while (formated[i])
	{
		if (formated[i] == '(')
			parenthesis_num++;
		else if (formated[i] == ')')
			parenthesis_num--;
		if (parenthesis_num == 0)
			break ;
		(*bet_parent)[x] = formated[i];
		x++;
		i++;
	}
}
