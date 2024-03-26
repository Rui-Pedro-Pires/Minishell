/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_out_pipe_case.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:45:59 by ruiolive          #+#    #+#             */
/*   Updated: 2024/03/26 14:25:51 by ruiolive         ###   ########.fr       */
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

void	change_stdout_pipe_case(t_pipes *node, int *stdout, int i)
{
	if (node->pipe_type == S_PIPE)
	{
		pipe(node->pipe_memmory.fd[i]);
		dup2(node->pipe_memmory.fd[i][1], STDOUT_FILENO);
	}
	else
	{
		dup2(*stdout, STDOUT_FILENO);
		close(*stdout);
	}
}

void	change_stdin_pipe_case(t_pipes *node, int i)
{
	if (i != 0)
	{
		close(node->pipe_memmory.fd[i - 1][1]);
		dup2(node->pipe_memmory.fd[i - 1][0], STDIN_FILENO);
	}
}

void	close_stdin_pipe_case(t_pipes *node, int i)
{
	if (i != 0)
		close(node->pipe_memmory.fd[i - 1][0]);
}

void	check_for_execution_to_file(t_pipes *node, int *status)
{
	if (node->in_out.output_type == REDIRECT_OUTPUT || \
		node->in_out.output_type == APPEND_OUTPUT)
		*status = execute_to_file(node, *status);
	else
		*status = execute_to_stdout(node, *status);
}
