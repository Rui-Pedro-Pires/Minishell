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
	while (str[x] && str[x] != ' ' && str[x] != '\'' && str[x] != '\"')
	{
		x++;
		y++;
	}
	str_condition = ft_calloc(sizeof(char), y + 1);
	x = i;
	y = 0;
	while (str[x] && str[x] != ' ' && str[x] != '\'' && str[x] != '\"')
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

	while (*i > 0 && str[(*i)] != ' ' && str[(*i)] != '\'' && str[(*i)] != '\"')
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
	if (save_redir == 1 && count_files(files) > 1)
		return (1);
	else
	{
		while (node->input_string[x] && !ft_strchr(" \'\"",
				node->input_string[x]))
			x++;
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
	}
	return (0);
}

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
	while (x > 0 && i > 0)
	{
		if (file[i] != condition[x])
			return (0);
		i--;
		x--;
	}
	if (x != 0)
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

void	insert_trimmed_files(char **trimmed_files, char *file_to_add)
{
	if (!(*trimmed_files))
		*trimmed_files = ft_strdup(file_to_add);
	else
		*trimmed_files = str_join_with_space(*trimmed_files, file_to_add, 1);
}

char	*trim_files(char *files, char *str_condition)
{
	char	*trimmed_files;
	char	**splited_files;
	char	*condition;
	int		i;

	i = 0;
	trimmed_files = NULL;
	condition = remove_dupp_wild(str_condition);
	splited_files = ft_split_ignore_quotes(files, " \t\n");
	while (splited_files[i])
	{
		if (check_to_add(splited_files[i], condition))
			insert_trimmed_files(&trimmed_files, splited_files[i]);
		i++;
	}
	free_args(splited_files);
	free(condition);
	return (trimmed_files);
}

int	search_redir(char *str, int i)
{
	while (i > 0)
	{
		if (ft_strchr("|><", str[i]))
			return (1);
		i--;
	}
	return (0);
}

int	redir_wildcard(t_pipes *node, int *i, char *files, char **str_condition)
{
	char	*trimmed_files;
	int		save_if_redir;

	save_if_redir = search_redir(node->input_string, *i);
	*str_condition = wildcard_checker(node->input_string, i);
	if (check_only_wildcard(*str_condition) == 0)
	{
		if (insert_files_into_str(node, files, i, save_if_redir))
			return (free(*str_condition), 1);
	}
	else
	{
		trimmed_files = trim_files(files, *str_condition);
		if (!trimmed_files)
		{
			*i += ft_strlen(*str_condition);
			return (free(*str_condition), 2);
		}
		if (insert_files_into_str(node, trimmed_files, i, save_if_redir))
			return (free(*str_condition), 1);
		free(trimmed_files);
	}
	return (0);
}

char	*wildcards(t_pipes *node)
{
	int		i;
	char	*files;
	char	*str_condition;

	int save_return ;
	i = 0;
	files = listfiles(".");
	if (!files)
		return (0);
	else
	{
		while (node->input_string[i])
		{
			if (node->input_string[i] == '*')
			{
				save_return = redir_wildcard(node, &i, files, &str_condition);
				if (save_return == 2)
					continue ;
				else if (save_return == 1)
					return (str_condition);
				free(str_condition);
			}
			i += all_quotes_ignore(node->input_string + i);
		}
	}
	return (NULL);
}
