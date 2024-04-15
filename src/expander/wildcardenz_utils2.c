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

int	mid_condition(char **ptr, char *condition, char *file, int *i);
int	mid_condition_begin_case(char **ptr, char *condition, char *file, int *i);

char	*get_mid(char *str, int *i)
{
	char	*str_condition;
	int		x;

	x = 0;
	str_condition = NULL;
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
				return (free(mid_cond), 0);
			file = ptr;
			free(mid_cond);
		}
		else
			i++;
	}
	return (1);
}

int	all_cases_file_name(char *file, char *condition)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = condition;
	while (condition[i])
	{
		if (condition[i] != '*' && ptr == condition + i)
		{
			if (mid_condition_begin_case(&ptr, condition, file, &i) == 0)
				return (0);
		}
		else if (condition[i] != '*')
		{
			if (mid_condition(&ptr, condition, file, &i) == 0)
				return (0);
		}
		else
			i++;
	}
	return (1);
}

int	mid_condition(char **ptr, char *condition, char *file, int *i)
{
	char	*mid_cond;

	mid_cond = get_mid(condition + *i, i);
	if (!condition[(*i)])
	{
		if (ends_with_file_name(file, mid_cond) == 0)
		{
			free(mid_cond);
			return (0);
		}
	}
	*ptr = ft_strnstr(file, mid_cond, ft_strlen(file));
	if (!(*ptr))
	{
		free(mid_cond);
		return (0);
	}
	*ptr = file;
	free(mid_cond);
	return (1);
}

int	mid_condition_begin_case(char **ptr, char *condition, char *file, int *i)
{
	char	*mid_cond;

	mid_cond = get_mid(condition + *i, i);
	if (ft_strncmp(file, mid_cond, ft_strlen(mid_cond)))
		return (free(mid_cond), 0);
	*ptr = ft_strnstr(file, mid_cond, ft_strlen(file));
	*ptr = file;
	free(mid_cond);
	return (1);
}
