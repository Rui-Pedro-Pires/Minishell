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

char		**empty_element_remover(char **array);

int	init_data(t_pipes *node)
{
	int		i;
	int		status;

	node->in_out.input_type = NO_INPUT;
	node->in_out.output_type = NO_OUTPUT;
	if (!wildcards(node))
		status = define_input_and_output(node);
	else
		status = 1;
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
