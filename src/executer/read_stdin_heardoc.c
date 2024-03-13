/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin_heardoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive  <ruiolive@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:15:37 by ruiolive          #+#    #+#             */
/*   Updated: 2024/03/13 09:15:37 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	read_from_stdin(t_pipes *head, char *to_be_read)
{
	int		pid1;
	int		pid2;
	int		checker1;
	int		checker2;
	int		fd_in[2];

	if (pipe(fd_in))
		return (0);
	pid1 = fork();
	write_pipe_stdin(head, fd_in, to_be_read, pid1);
	pid2 = fork();
	read_pipe_stdin(head, fd_in, pid2);
	close(fd_in[0]);
	close(fd_in[1]);
	waitpid(pid1, &checker1, 0);
	waitpid(pid2, &checker2, 0);
	free(to_be_read);
	to_be_read = NULL;
	if (checker1 != 0 || checker2 != 0)
		return (0);
	return (1);
}

int	read_from_heardoc(t_pipes *head, char *to_be_read)
{
	int		pid1;
	int		pid2;
	int		checker1;
	int		checker2;
	int		fd_in[2];

	if (pipe(fd_in))
		return (0);
	pid1 = fork();
	write_pipe_heardoc(head, fd_in, to_be_read, pid1);
	pid2 = fork();
	read_pipe_heardoc(head, fd_in, pid2);
	close(fd_in[0]);
	close(fd_in[1]);
	waitpid(pid1, &checker1, 0);
	waitpid(pid2, &checker2, 0);
	if (checker1 != 0 || checker2 != 0)
		return (0);
	return (1);
}
