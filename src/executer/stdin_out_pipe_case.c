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

int	list_size(t_pipes *head)
{
	int	i;

	if (!head)
		return (0);
	i = 0;
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

void	check_for_execution_to_file(t_pipes *node, int *status)
{
	if (node->in_out.output_type == REDIRECT_OUTPUT || \
		node->in_out.output_type == APPEND_OUTPUT)
	{
		dup2(node->in_out.fd_out, STDOUT_FILENO);
		close(node->in_out.fd_out);
	}
	*status = execute_command(node);
}
