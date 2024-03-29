/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin_heardoc_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:14:07 by ruiolive          #+#    #+#             */
/*   Updated: 2024/03/28 17:22:11 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	write_pipe_stdin(t_pipes *head)
{
	int	fd_in[2];
	int	stdout;

	if (pipe(fd_in))
		return ;
	stdout = dup(STDOUT_FILENO);
	dup2(fd_in[1], STDOUT_FILENO);
	if (head->in_out.data_read)
	{
		printf("%s", head->in_out.data_read);
		free(head->in_out.data_read);
		head->in_out.data_read = NULL;
	}
	if (head->in_out.output_file)
	{
		free(head->in_out.output_file);
		head->in_out.output_file = NULL;
	}
	close(fd_in[1]);
	dup2(stdout, STDOUT_FILENO);
	close(stdout);
	dup2(fd_in[0], STDIN_FILENO);
}

void	write_pipe_heardoc(t_pipes *head)
{
	int	fd_in[2];
	int	stdout;

	if (pipe(fd_in))
		return ;
	stdout = dup(STDOUT_FILENO);
	dup2(fd_in[1], STDOUT_FILENO);
	if (head->init.heardocs[*head->init.heardoc_index])
		printf("%s", head->init.heardocs[*head->init.heardoc_index]);
	if (head->in_out.output_file)
	{
		free(head->in_out.output_file);
		head->in_out.output_file = NULL;
	}
	close(fd_in[1]);
	dup2(stdout, STDOUT_FILENO);
	close(stdout);
	dup2(fd_in[0], STDIN_FILENO);
}
