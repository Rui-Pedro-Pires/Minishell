/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_in_out_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:49:17 by ruiolive          #+#    #+#             */
/*   Updated: 2024/04/06 20:53:10 by ruiolive         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

int	heardoc(t_pipes *node, int i)
{
	if (!ft_strncmp(node->input_string + i, "<<", 2))
	{
		node->in_out.input_type = HEARDOC;
		(*node->init->heardoc_index)++;
		rechange_str(node, i, 2);
	}
	return (0);
}

int	redirect_input(t_pipes *node, int i)
{
	char	*file_name;

	if (node->input_string[i] == '<')
	{
		node->in_out.input_type = REDIRECT_INPUT;
		file_name = search_file_name(node, node->input_string + i);
		rechange_str(node, i, 1);
		node->in_out.fd = open(file_name, O_RDONLY);
		if (node->in_out.fd < 0)
		{
			print_error("minishell: ");
			perror(file_name);
			free(file_name);
			return (1);
		}
		free(file_name);
	}
	return (0);
}

int	redirect_output(t_pipes *node, int i)
{
	if (node->input_string[i] == '>')
	{
		if (redirect_output_case(node, i) != 0)
		{
			rechange_str(node, i, 1);
			return (1);
		}
		rechange_str(node, i, 1);
	}
	return (0);
}

int	redir_pipe(t_pipes *node, int i)
{
	if (!ft_strncmp(node->input_string + i, ">|", 2))
	{
		if (redirect_output_case(node, i + 1) != 0)
		{
			rechange_str(node, i, 2);
			return (1);
		}
		rechange_str(node, i, 2);
	}
	return (0);
}

int	append_output(t_pipes *node, int i)
{
	if (!ft_strncmp(node->input_string + i, ">>", 2))
	{
		if (append_output_case(node, i) != 0)
		{
			rechange_str(node, i, 2);
			return (1);
		}
		rechange_str(node, i, 2);
	}
	return (0);
}
