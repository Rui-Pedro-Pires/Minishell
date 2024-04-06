/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin_heardoc_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:14:07 by ruiolive          #+#    #+#             */
/*   Updated: 2024/04/06 20:10:16 by ruiolive         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

int	write_pipe_stdin(t_pipes *head)
{
	int	fd;

	if (head->in_out.input_type == REDIRECT_INPUT)
	{
		fd = open(head->in_out.input_file, O_RDONLY);
		if (fd > 0)
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		free(head->in_out.input_file);
		head->in_out.input_file = NULL;
	}
	return (0);
}

void	write_pipe_heardoc(t_pipes *head)
{
	int	fd_in[2];
	int	stdout;

	if (head->init->heardocs[*head->init->heardoc_index])
	{
		if (pipe(fd_in))
			return ;
		stdout = dup(STDOUT_FILENO);
		dup2(fd_in[1], STDOUT_FILENO);
		close(fd_in[1]);
		printf("%s", head->init->heardocs[*head->init->heardoc_index]);
		dup2(stdout, STDOUT_FILENO);
		close(stdout);
		dup2(fd_in[0], STDIN_FILENO);
		close(fd_in[0]);
	}
}
