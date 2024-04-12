/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcardenz_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:42:08 by jorteixe          #+#    #+#             */
/*   Updated: 2024/04/12 12:42:11 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*get_mid(char *str, int *i)
{
	char	*str_condition;
	int		x;

	x = 0;
	while (str[x] && str[x] != '*')
	{
		x++;
		(*i)++;
	}
	str_condition = ft_calloc(sizeof(char), x + 1);
	x = 0;
	while (str[x] && str[x] != '*')
	{
		str_condition[x] = str[x];
		x++;
	}
	return (str_condition);
}

int	middle_with_file_name(char *file, char *condition)
{
	int		i;
	char	*mid_cond;
	char	*ptr;

	i = 0;
	while (condition[i])
	{
		if (condition[i] != '*')
		{
			mid_cond = get_mid(condition + i, &i);
			ptr = ft_strnstr(file, mid_cond, ft_strlen(file));
			if (!ptr)
				return (0);
			file = ptr;
		}
		else
			i++;
	}
	return (1);
}

int	all_cases_file_name(char *file, char *condition)
{
	int		i;
	char	*mid_cond;
	char	*ptr;

	i = 0;
	ptr = condition;
	while (condition[i])
	{
		if (condition[i] != '*' && ptr == condition)
		{
			mid_cond = get_mid(condition + i, &i);
			if (ft_strncmp(file, mid_cond, ft_strlen(mid_cond)))
				return (0);
			ptr = ft_strnstr(file, mid_cond, ft_strlen(file));
			ptr = file;
		}
		else if (condition[i] != '*')
		{
			mid_cond = get_mid(condition + i, &i);
			if (!condition[i])
			{
				if (ends_with_file_name(file, mid_cond) == 0)
					return (0);
			}
			ptr = ft_strnstr(file, mid_cond, ft_strlen(file));
			if (!ptr)
				return (0);
			ptr = file;
		}
		else
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
