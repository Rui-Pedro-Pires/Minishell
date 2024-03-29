/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_out_pipe_case.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:45:59 by ruiolive          #+#    #+#             */
/*   Updated: 2024/03/29 11:44:27 by ruiolive         ###   ########.fr       */
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
	int	fd;
	int	stdout;

	if (node->in_out.output_type == REDIRECT_OUTPUT || \
		node->in_out.output_type == APPEND_OUTPUT)
	{
		fd = open(node->in_out.output_file, O_APPEND | O_WRONLY);
		if (fd < 0)
		{
			print_error("minishell: ");
			print_error(node->in_out.output_file);
			print_error(": Permission denied\n");
			free(node->in_out.output_file);
			*status = 1;
			return ;
		}
		stdout = dup(STDOUT_FILENO);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	*status = execute_command(node);
	if (node->in_out.output_type == REDIRECT_OUTPUT || \
		node->in_out.output_type == APPEND_OUTPUT)
	{
		dup2(stdout, STDOUT_FILENO);
		close(stdout);
		free(node->in_out.output_file);
	}
}
