/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin_heardoc_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:14:07 by ruiolive          #+#    #+#             */
/*   Updated: 2024/04/06 15:38:17 by ruiolive         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

void	write_pipe_stdin(t_pipes *head)
{
	int	fd_in[2];
	int	stdout;

	if (head->in_out.data_read)
	{
		if (pipe(fd_in))
			return ;
		write(1, head->in_out.data_read, ft_strlen(head->in_out.data_read));
		// stdout = dup(STDOUT_FILENO);
		// dup2(fd_in[1], STDOUT_FILENO);
		// close(fd_in[1]);
		// write(1, head->in_out.data_read, ft_strlen(head->in_out.data_read));
		// // printf("%s", head->in_out.data_read);
		// dup2(stdout, STDOUT_FILENO);
		// close(stdout);
		// free(head->in_out.data_read);
		// head->in_out.data_read = NULL;
		// dup2(fd_in[0], STDIN_FILENO);
		// close(fd_in[0]);
	}
	// if (head->in_out.output_file)
	// {
	// 	free(head->in_out.output_file);
	// 	head->in_out.output_file = NULL;
	// }
}

void	write_pipe_heardoc(t_pipes *head)
{
	int	fd_in[2];
	int	stdout;

	if (head->init->heardocs[*head->init->heardoc_index])
	{
		if (pipe(fd_in))
			return ;
		// head->init.heardocs[*head->init.heardoc_index] 
		// = check_quotes_n_expand(head, head->init.heardocs[*head->init.heardoc_index]);
		stdout = dup(STDOUT_FILENO);
		dup2(fd_in[1], STDOUT_FILENO);
		close(fd_in[1]);
		printf("%s", head->init->heardocs[*head->init->heardoc_index]);
		dup2(stdout, STDOUT_FILENO);
		close(stdout);
		dup2(fd_in[0], STDIN_FILENO);
		close(fd_in[0]);
	}
	// if (head->in_out.output_file)
	// {
	// 	free(head->in_out.output_file);
	// 	head->in_out.output_file = NULL;
	// }
}
