/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:55:35 by ruiolive          #+#    #+#             */
/*   Updated: 2024/03/20 11:36:54 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_to_file(t_pipes *head, int status)
{
	int	fd;
	int	stdout;

	fd = open(head->in_out.output_file, O_APPEND | O_WRONLY);
	if (fd < 0)
	{
		free(head->in_out.output_file);
		return (perror("minishell"), 0);
	}
	stdout = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	status = execute_command(head);
	if ((status == 0 && head->pipe_type == D_PIPE) || status == 0)
	{
		dup2(stdout, 1);
		close(stdout);
		free(head->in_out.output_file);
		return (0);
	}
	dup2(stdout, 1);
	close(stdout);
	free(head->in_out.output_file);
	return (1);
}

int	execute_to_stdout(t_pipes *head, int status)
{
	status = execute_command(head);
	if ((status == 0 && head->pipe_type == D_PIPE) || status == 0)
		return (0);
	return (1);
}

void	init_data(t_pipes *node)
{
	node->in_out.input_type = NO_INPUT;
	node->in_out.output_type = NO_OUTPUT;
	node->in_out.output_file = NULL;
	node->in_out.input_file = NULL;
	define_input_and_output(node);
	node->data.command_n_args = ft_split(node->input_string, ' ');
	command_decider(node);
}

int	**alloc_memory_for_fd(int size)
{
	int	i;
	int	**fd;

	i = 0;
	fd = malloc(sizeof(int *) * size);
	while (i < size)
	{
		fd[i] = malloc(sizeof(int) * 2);
		i++;
	}
	return (fd);
}

void	free_fd(int size, int **fd)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}
