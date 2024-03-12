/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/25 09:33:58 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	fill_data(t_pipes *node, int status)
{
	node->in_out.input_type = NO_INPUT;
	node->in_out.output_type = NO_OUTPUT;
	node->in_out.output_file = NULL;
	node->in_out.input_file = NULL;
	define_in_out(node);
	node->data.command_n_args = ft_split(node->input_string, ' ');
	if (!command_decider1(node, status) && !command_decider2(node, status))
		node->data.command_type = NOT_BUILTIN;
	return (0);
}
