/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcardenz_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:40:28 by jorteixe          #+#    #+#             */
/*   Updated: 2024/04/12 12:41:21 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	while (i >= 0)
	{
		if (i - 1 >= 0 && str[i] == '<' && str[i - 1] == '<')
			return (2);
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
	if (save_if_redir == 2)
		return (2);
	if (check_only_wildcard(*str_condition) == 0)
	{
		if (insert_files_into_str(node, files, i, save_if_redir))
			return (1);
	}
	else
	{
		trimmed_files = trim_files(files, *str_condition);
		if (!trimmed_files)
			return (2);
		if (insert_files_into_str(node, trimmed_files, i, save_if_redir))
		{
			free(trimmed_files);
			return (1);
		}
		free(trimmed_files);
	}
	return (0);
}

char	*wildcards(t_pipes *node, char *files)
{
	int		i;
	char	*str_condition;
	int		save_return;

	i = 0;
	str_condition = NULL;
	while (node->input_string[i])
	{
		if (node->input_string[i] == '*')
		{
			save_return = redir_wildcard(node, &i, files, &str_condition);
			if (save_return == 2)
			{
				i += ft_strlen(str_condition);
				free(str_condition);
				continue ;
			}
			else if (save_return == 1)
				return (str_condition);
			free(str_condition);
		}
		else
			i += all_quotes_ignore(node->input_string + i);
	}
	return (NULL);
}

void	insert_trimmed_files(char **trimmed_files, char *file_to_add)
{
	if (!(*trimmed_files))
		*trimmed_files = ft_strdup(file_to_add);
	else
		*trimmed_files = str_join_with_space(*trimmed_files, file_to_add, 1);
}
