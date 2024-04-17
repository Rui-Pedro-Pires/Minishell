/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heardoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:55:58 by ruiolive          #+#    #+#             */
/*   Updated: 2024/04/06 12:17:35 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char		**empty_element_rem(t_pipes *node);

static int	handle_wildcards(t_pipes *node)
{
	int		status;
	char	*return_value;
	char	*files;

	files = listfiles(".");
	if (!files)
	{
		status = define_input_and_output(node);
		return (status);
	}
	return_value = wildcards(node, files);
	free(files);
	if (!return_value)
		status = define_input_and_output(node);
	else
	{
		status = 1;
		print_error("minishell: ");
		print_error(return_value);
		print_error(": ambiguous redirect\n");
		free(return_value);
	}
	return (status);
}

static void	process_command_n_args(t_pipes *node, t_init *init)
{
	int	i;

	node->data.command_n_args = ft_split_ignore_quotes(node->input_string,
			" \t\n");
	i = 0;
	while (node->data.command_n_args[i] != NULL)
	{
		node->data.command_n_args[i] = check_quotes_n_expand(*init,
				node->data.command_n_args[i]);
		i++;
	}
	node->data.command_n_args = empty_element_rem(node);
	update_env_last_arg(node);
	update_sorted_env_last_arg(node);
}

int	init_data(t_pipes *node)
{
	int	status;

	node->in_out.input_type = NO_INPUT;
	node->in_out.output_type = NO_OUTPUT;
	status = handle_wildcards(node);
	process_command_n_args(node, node->init);
	command_decider(node);
	return (status);
}

char	**empty_element_rem(t_pipes *node)
{
	int		i;
	int		j;
	int		size;
	char	**clean_array;

	i = -1;
	j = 0;
	size = 0;
	if (!node->data.command_n_args)
		return (NULL);
	while (node->data.command_n_args[++i])
	{
		if (ft_strcmp(node->data.command_n_args[i], ""))
			size++;
	}
	clean_array = ft_calloc(size + 1, sizeof(char *));
	i = -1;
	while (node->data.command_n_args[++i])
	{
		if (ft_strcmp(node->data.command_n_args[i], ""))
			clean_array[j++] = ft_strdup(node->data.command_n_args[i]);
	}
	free_args(node->data.command_n_args);
	return (clean_array);
}
