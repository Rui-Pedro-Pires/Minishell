/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive  <ruiolive@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:27:46 by ruiolive          #+#    #+#             */
/*   Updated: 2024/04/11 10:31:07 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_str_condition(char *str, int i)
{
	char	*str_condition;
	int		x;
	int		y;

	x = i;
	y = 0;
	while (str[x] && !ft_strchr(" \t\n<>", str[x]))
	{
		x++;
		y++;
	}
	str_condition = ft_calloc(sizeof(char), y + 1);
	x = i;
	y = 0;
	while (str[x] && !ft_strchr(" \t\n<>", str[x]))
		str_condition[y++] = str[x++];
	return (str_condition);
}

int	check_only_wildcard(char *str_condition)
{
	int	x;

	x = 0;
	while (str_condition[x])
	{
		if (str_condition[x] != '*')
			return (1);
		x++;
	}
	return (0);
}

char	*wildcard_checker(char *str, int *i)
{
	char	*str_condition;

	while (*i > 0 && !ft_strchr(" \t\n<>", str[*i]))
		(*i)--;
	(*i)++;
	str_condition = get_str_condition(str, *i);
	return (str_condition);
}

int	count_files(char *files)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (files[i] != '\0')
	{
		while (files[i] && ft_strchr(" ", files[i]))
			i += all_quotes_ignore(files + i);
		if (files[i] != '\0')
			counter++;
		while (files[i] && !ft_strchr(" ", files[i]))
			i += all_quotes_ignore(files + i);
	}
	return (counter);
}

int	insert_files_into_str(t_pipes *node, char *files, int *i, int save_redir)
{
	int		x;
	int		j;
	int		y;
	char	*new_str;

	x = *i;
	j = -1;
	y = -1;
	while (node->input_string[x] && !ft_strchr(" \t\n<>",
			node->input_string[x]))
		x++;
	if (save_redir == 1 && count_files(files) > 1)
		return (1);
	new_str = ft_calloc(sizeof(char), ft_strlen(node->input_string) - (x
				- *i) + ft_strlen(files) + 1);
	while (++j < *i)
		new_str[j] = node->input_string[j];
	while (files[++y])
		new_str[j++] = files[y];
	while (node->input_string[x])
		new_str[j++] = node->input_string[x++];
	free(node->input_string);
	node->input_string = new_str;
	*i += y;
	return (0);
}
