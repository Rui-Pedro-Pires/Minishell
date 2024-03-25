/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin_heardoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:15:37 by ruiolive          #+#    #+#             */
/*   Updated: 2024/03/25 09:40:24 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	read_from_stdin(t_pipes *head, char *to_be_read)
{
	int		fd_in[2];

	if (pipe(fd_in))
		return (-1);
	write_pipe_stdin(head, fd_in, to_be_read);
	return (read_pipe_stdin(head, fd_in));
}

int	read_from_heardoc(t_pipes *head, char *to_be_read)
{
	int		fd_in[2];

	if (pipe(fd_in))
		return (0);
	write_pipe_heardoc(head, fd_in, to_be_read);
	return (read_pipe_heardoc(head, fd_in));
}
