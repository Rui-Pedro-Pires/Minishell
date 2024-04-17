/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_function.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive  <ruiolive@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:12:30 by ruiolive          #+#    #+#             */
/*   Updated: 2024/04/15 12:12:30 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	recursive_executer(t_pipes *current, int recursive, t_pipes *head)
{
	int		status;
	t_pipes	*curr;

	status = 0;
	curr = current;
	while (curr)
	{
		status = recursive_down(curr, head);
		if (status == 0 && curr->pipe_type == D_PIPE)
		{
			while (curr && curr->pipe_type != AMPER)
				curr = curr->next;
		}
		if (curr)
			curr = curr->next;
	}
	if (status != 0 && recursive == 1)
		return (status);
	return (status);
}

int	recursive_down(t_pipes *curr, t_pipes *head)
{
	int	status;

	if (!curr)
		return (-1);
	if (check_for_dbpipe_dbamper(curr->input_string))
		return (recursive_executer(curr->down, 1, head));
	status = recursive_down(curr->down, head);
	if (status != -1)
		return (status);
	return (list_iterator_executer(curr, head));
}

int	list_iterator_executer(t_pipes *curr, t_pipes *head)
{
	int	status;
	int	size;

	status = 0;
	size = list_size(curr);
	if (size == 1)
		return (single_command(curr, head));
	loop_list_and_execute(curr, head, size, &status);
	return (status);
}
