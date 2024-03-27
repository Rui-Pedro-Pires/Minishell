/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_out_pipe_case.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:45:59 by ruiolive          #+#    #+#             */
/*   Updated: 2024/03/27 10:57:45 by ruiolive         ###   ########.fr       */
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
			free(node->in_out.output_file);
			perror("minishell");
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
