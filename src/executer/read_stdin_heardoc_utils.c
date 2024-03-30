/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin_heardoc_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:14:07 by ruiolive          #+#    #+#             */
/*   Updated: 2024/03/29 16:21:54 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	write_pipe_stdin(t_pipes *head)
{
	int	fd_in[2];

	if (pipe(fd_in))
		return ;
	if (head->in_out.data_read)
	{
		write(fd_in[1], head->in_out.data_read, ft_strlen(head->in_out.data_read));
		free(head->in_out.data_read);
		head->in_out.data_read = NULL;
	}
	if (head->in_out.output_file)
	{
		free(head->in_out.output_file);
		head->in_out.output_file = NULL;
	}
	close(fd_in[1]);
	dup2(fd_in[0], STDIN_FILENO);
}

void	write_pipe_heardoc(t_pipes *head)
{
	int	fd_in[2];

	if (pipe(fd_in))
		return ;
	if (head->init.heardocs[*head->init.heardoc_index])
	{
		// head->init.heardocs[*head->init.heardoc_index] 
		// = check_quotes_n_expand(head, head->init.heardocs[*head->init.heardoc_index]);
		write(fd_in[1], head->init.heardocs[*head->init.heardoc_index],\
		ft_strlen(head->init.heardocs[*head->init.heardoc_index]));
	}
	if (head->in_out.output_file)
	{
		free(head->in_out.output_file);
		head->in_out.output_file = NULL;
	}
	close(fd_in[1]);
	dup2(fd_in[0], STDIN_FILENO);
}
