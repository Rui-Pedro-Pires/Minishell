/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:55:35 by ruiolive          #+#    #+#             */
/*   Updated: 2024/04/02 17:03:33 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**join_args_wildcards(char **s1, char **s2, int i);
static int	check_for_wildcard(char *str);
char		**empty_element_remover(char **array);

int	init_data(t_pipes *node)
{
	int		i;
	int		status;
	char	**files;

	node->in_out.input_type = NO_INPUT;
	node->in_out.output_type = NO_OUTPUT;
	node->in_out.output_file = NULL;
	node->in_out.input_file = NULL;
	node->in_out.data_read = NULL;
	status = define_input_and_output(node);
	node->data.command_n_args = ft_split_ignore_quotes(node->input_string,
			" \t\n");
	files = NULL;
	i = 0;
	while (node->data.command_n_args[i] != NULL)
	{
		if (check_for_wildcard(node->data.command_n_args[i]) == 0)
		{
			files = listfiles(".", node->data.command_n_args[i]);
			node->data.command_n_args = join_args_wildcards(node->data.command_n_args,
					files, i);
		}
		node->data.command_n_args[i] = check_quotes_n_expand(*node->init,
				node->data.command_n_args[i]);
		i++;
	}
	node->data.command_n_args = empty_element_remover(node->data.command_n_args);
	command_decider(node);
	return (status);
}

static char	**join_args_wildcards(char **s1, char **s2, int x)
{
	char	**after_args;
	char	**before_args;
	char	**new_str;
	int		i;
	int		n;

	if (!s2)
		return (s1);
	before_args = ft_calloc(sizeof(char *), x + 1);
	after_args = ft_calloc(sizeof(char *), array_size(s1) - x + 1);
	new_str = ft_calloc(sizeof(char *), array_size(s1) + array_size(s2));
	i = 0;
	n = 0;
	while (s1[i] && i < x)
		before_args[n++] = ft_strdup(s1[i++]);
	x++;
	n = 0;
	while (s1[x])
		after_args[n++] = ft_strdup(s1[x++]);
	new_str = ft_strjoin_files(before_args, s2);
	new_str = ft_strjoin_files(new_str, after_args);
	free_args(s1);
	return (new_str);
}

static int	check_for_wildcard(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr("*", str[i]))
			return (0);
		i += all_quotes_ignore(str + i);
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
	clean_array = calloc(size + 1, sizeof(char *));
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