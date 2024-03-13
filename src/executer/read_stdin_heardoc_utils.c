/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_heardoc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive  <ruiolive@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:14:07 by ruiolive          #+#    #+#             */
/*   Updated: 2024/03/13 09:14:07 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	error_status(t_pipes *head, char	**env_array);

void	write_pipe_stdin(t_pipes *head, int fd_in[2], \
char *to_be_read, int pid1)
{
	if (pid1 < 0)
		ft_exit(head, 0);
	else if (pid1 == 0)
	{
		dup2(fd_in[1], STDOUT_FILENO);
		close(fd_in[0]);
		close(fd_in[1]);
		if (to_be_read)
		{
			printf("%s", to_be_read);
			free(to_be_read);
			to_be_read = NULL;
		}
		if (head->in_out.output_file)
		{
			free(head->in_out.output_file);
			head->in_out.output_file = NULL;
		}
		ft_exit(head, 1);
	}
}

void	read_pipe_stdin(t_pipes *head, int fd_in[2], int pid2)
{
	char	**env_array;
	int		status;

	if (pid2 < 0)
		ft_exit(head, 0);
	else if (pid2 == 0)
	{
		dup2(fd_in[0], STDIN_FILENO);
		close(fd_in[0]);
		close(fd_in[1]);
		env_array = envlist_to_array(head->init.envs);
		status = execve(head->data.command_n_args[0], head->data.command_n_args,
				env_array);
		if (status == -1)
		{
			error_status(head, 0);
			free(head->in_out.data_read);
			head->in_out.data_read = NULL;
			ft_exit(head, 0);
		}
	}
}

void	write_pipe_heardoc(t_pipes *head, int fd_in[2], \
char *to_be_read, int pid1)
{
	if (pid1 < 0)
		ft_exit(head, 0);
	if (pid1 == 0)
	{
		dup2(fd_in[1], STDOUT_FILENO);
		close(fd_in[0]);
		close(fd_in[1]);
		if (to_be_read)
			printf("%s", to_be_read);
		if (head->in_out.output_file)
		{
			free(head->in_out.output_file);
			head->in_out.output_file = NULL;
		}
		ft_exit(head, 1);
	}
}

void	read_pipe_heardoc(t_pipes *head, int fd_in[2], int pid2)
{
	char	**env_array;
	int		status;

	if (pid2 < 0)
		ft_exit(head, 0);
	else if (pid2 == 0)
	{
		dup2(fd_in[0], STDIN_FILENO);
		close(fd_in[0]);
		close(fd_in[1]);
		env_array = envlist_to_array(head->init.envs);
		status = execve(head->data.command_n_args[0], head->data.command_n_args,
				env_array);
		if (status == -1)
		{
			error_status(head, env_array);
			ft_exit(head, 0);
		}
	}
}

static void	error_status(t_pipes *head, char	**env_array)
{
	if (errno == ENOENT)
		perror("Command not found\n");
	else
		perror("execve");
	free_args(env_array);
	if (head->in_out.output_file)
	{
		free(head->in_out.output_file);
		head->in_out.output_file = NULL;
	}
}
