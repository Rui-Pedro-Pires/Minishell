/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcardenz_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:42:56 by jorteixe          #+#    #+#             */
/*   Updated: 2024/04/12 12:43:14 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*push_char(char *str, char to_push)
{
	char	*pushed_str;
	int		i;

	i = -1;
	if (!str)
	{
		pushed_str = ft_calloc(sizeof(char), 2);
		pushed_str[0] = to_push;
		return (pushed_str);
	}
	pushed_str = ft_calloc(sizeof(char), ft_strlen(str) + 2);
	while (str[++i])
		pushed_str[i] = str[i];
	pushed_str[i] = to_push;
	free(str);
	return (pushed_str);
}

char	*remove_dupp_wild(char *condition)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = NULL;
	while (condition[i])
	{
		if (condition[i] == '*')
		{
			new_str = push_char(new_str, condition[i]);
			while (condition[i] && condition[i] == '*')
				i++;
		}
		else
			new_str = push_char(new_str, condition[i++]);
	}
	return (new_str);
}

int	ends_with_file_name(char *file, char *condition)
{
	int	i;
	int	x;

	i = ft_strlen(file) - 1;
	x = ft_strlen(condition) - 1;
	if (x == 0)
	{
		if (file[i] == condition[x])
			return (1);
	}
	while (x >= 0 && i >= 0 && condition[x] != '*')
	{
		if (file[i] != condition[x])
			return (0);
		i--;
		x--;
	}
	if (x < 0)
		return (1);
	if (x != 0 && condition[x] != '*')
		return (0);
	return (1);
}

int	starts_with_file_name(char *file, char *condition)
{
	int	i;

	i = 0;
	while (condition[i + 1])
	{
		if (file[i] != condition[i])
			return (0);
		i++;
	}
	return (1);
}

int	check_to_add(char *file, char *condition)
{
	int	size_condition;

	size_condition = ft_strlen(condition);
	if (ft_strchr("*", condition[0]) && !ft_strchr(condition + 1, '*'))
		return (ends_with_file_name(file, condition));
	else if (ft_strchr("*", condition[size_condition - 1])
		&& !ft_strnstr(condition, "*", size_condition - 1))
		return (starts_with_file_name(file, condition));
	else if (ft_strchr("*", condition[0]) && ft_strchr("*",
			condition[size_condition - 1]))
		return (middle_with_file_name(file, condition));
	else
		return (all_cases_file_name(file, condition));
	return (0);
}
