/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:55:35 by ruiolive          #+#    #+#             */
/*   Updated: 2024/04/06 20:49:58 by ruiolive         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

static int	wildcards(t_pipes *node);
char		**empty_element_remover(char **array);

int	init_data(t_pipes *node)
{
	int		i;
	int		status;

	node->in_out.input_type = NO_INPUT;
	node->in_out.output_type = NO_OUTPUT;
	wildcards(node);
	status = define_input_and_output(node);
	node->data.command_n_args = ft_split_ignore_quotes(node->input_string,
			" \t\n");
	i = 0;
	while (node->data.command_n_args[i] != NULL)
	{
		node->data.command_n_args[i] = check_quotes_n_expand(*node->init,
				node->data.command_n_args[i]);
		i++;
	}
	node->data.command_n_args = empty_element_remover(node->data.command_n_args);
	command_decider(node);
	return (status);
}

char	*get_str_condition(char *str, int i)
{
	char	*str_condition;
	int		x;
	int		y;

	x = i;
	y = 0;
	while (str[x] && str[x] != ' ')
	{
		x++;
		y++;
	}
	str_condition = ft_calloc(sizeof(char), y + 1);
	x = i;
	y = 0;
	while (str[x] && str[x] != ' ')
		str_condition[y++] = str[x++];
	return (str_condition);
}

char	*wildcard_checker(char *str, int *i)
{
	char	*str_condition;
	int		x;

	x = 0;
	while (*i > 0 && str[(*i)] != ' ')
		(*i)--;
	(*i)++;
	str_condition = get_str_condition(str, *i);
	while (str_condition[x])
	{
		if (str_condition[x] != '*')
			return (str_condition);
		x++;
	}
	return (free(str_condition), NULL);
}

int	insert_files_into_str(t_pipes *node, char *files, int *i)
{
	int		x;
	int		j;
	int		y;
	int		size;
	char	*new_str;
	
	x = *i;
	j = -1;
	y = -1;
	while (node->input_string[x] && node->input_string[x] != ' ')
		x++;
	size = ft_strlen(node->input_string) - (x - *i) + ft_strlen(files) + 1;
	new_str = ft_calloc(sizeof(char), size);
	while (++j < *i)
		new_str[j] = node->input_string[j];
	while (files[++y])
		new_str[j++] = files[y];
	while (node->input_string[x])
		new_str[j++] = node->input_string[x++];
	free(node->input_string);
	node->input_string = new_str;
	*i += y;
	return (1);
}

static int	wildcards(t_pipes *node)
{
	int			i;
	char	*files;
	// char	*trimmed_files;
	char	*str_condition;

	i = 0;
	files = listfiles(".");
	while (node->input_string[i])
	{
		if (node->input_string[i] == '*')
		{
			str_condition = wildcard_checker(node->input_string, &i);
			if (!str_condition)
				insert_files_into_str(node, files, &i);
			// else
			// {
			// 	trimmed_files = trim_files(files, str_condition);
			// 	insert_files_into_str(node, trimmed_files, &i);
			// }
		}
		i += all_quotes_ignore(node->input_string + i);
	}
	return (1);
}

char	**empty_element_remover(char **array)
{
	int i;
	int j;
	int size;
	char **clean_array;
	i = 0;
	j = 0;
	size = 0;
	while (array[i])
	{
		if (!ft_strcmp(array[i], ""))
			size++;
		i++;
	}
	clean_array = ft_calloc(size + 1, sizeof(char *));
	i = 0;
	while (array[i])
	{
		if (!ft_strcmp(array[i], ""))
		{
			clean_array[j] = ft_strdup(array[i]);
			j++;
		}
		i++;
	}
	free_args(array);
	return (clean_array);
}
