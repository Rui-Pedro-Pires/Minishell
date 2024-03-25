/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_in_out_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:49:17 by ruiolive          #+#    #+#             */
/*   Updated: 2024/03/25 18:42:10 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	heardoc(t_pipes *node, int i)
{
	if (!ft_strncmp(node->input_string + i, "<<", 2))
	{
		node->in_out.input_type = HEARDOC;
		node->init.heardoc_index++;
		rechange_str(node, i, 2);
	}
	return (0);
}

int	redirect_input(t_pipes *node, int i)
{
	int	fd;

	if (node->input_string[i] == '<')
	{
		node->in_out.input_type = REDIRECT_INPUT;
		if (node->in_out.input_file)
		{
			free(node->in_out.input_file);
			node->in_out.input_file = NULL;
		}
		node->in_out.input_file = search_file_name(node->input_string + i);
		rechange_str(node, i, 1);
		fd = open(node->in_out.input_file, O_RDONLY);
		if (fd < 0)
			return (-1);
	}
	return (0);
}

int	redirect_output(t_pipes *node, int i)
{
	if (node->input_string[i] == '>')
	{
		if (redirect_output_case(node, i) == -1)
		{
			rechange_str(node, i, 1);
			return (-1);
		}
		rechange_str(node, i, 1);
	}
	return (0);
}

int	redir_pipe(t_pipes *node, int i)
{
	if (!ft_strncmp(node->input_string + i, ">|", 2))
	{
		if (redirect_output_case(node, i + 1) == -1)
		{
			rechange_str(node, i, 2);
			return (-1);
		}
		rechange_str(node, i, 2);
	}
	return (0);
}

int	append_output(t_pipes *node, int i)
{
	if (!ft_strncmp(node->input_string + i, ">>", 2))
	{
		if (append_output_case(node, i) == -1)
		{
			rechange_str(node, i, 2);
			return (-1);
		}
		rechange_str(node, i, 2);
	}
	return (0);
}
