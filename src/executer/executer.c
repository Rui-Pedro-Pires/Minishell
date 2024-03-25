/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:17:21 by jorteixe          #+#    #+#             */
/*   Updated: 2024/03/25 10:04:00 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	recursive_executer(t_pipes *head, int recursive)
{
	int	status;

	status = 0;
	while (head)
	{
		status = recursive_down(head);
		if (status == 0 && head->pipe_type == D_PIPE)
		{
			while (head && head->pipe_type != AMPER)
				head = head->next;
		}
		if (head)
			head = head->next;
	}
	if (status != 0 && recursive == 1)
		return (status);
	return (status);
}

int	recursive_down(t_pipes *head)
{
	int	status;

	if (!head)
		return (2);
	if (check_for_dbpipe_dbamper(head->input_string))
		return (recursive_executer(head->down, 1));
	status = recursive_down(head->down);
	if (status != 2)
		return (status);
	head->init.return_value = list_iterator_executer(head);
	return (head->init.return_value);
}

int	list_iterator_executer(t_pipes *head)
{
	int	i;
	int	x;
	int	status;
	int	stdin_out[2];
	int	**fd;
	int	size;
	int	*pid;

	i = 0;
	x = 0;
	status = 0;
	size = list_size(head);
	fd = alloc_memory_for_fd(size - 1);
	pid = malloc(sizeof(int) * size);
	while (head)
	{
		change_stdin_pipe_case(&stdin_out[1], &stdin_out[0], fd, i);
		change_stdout_pipe_case(head, fd, &stdin_out[1], i);
		init_data(head);
		if (head->data.command_type != NOT_BUILTIN && i == 0)
		{
			check_for_execution_to_file(head, &status);
			size--;
		}
		else
		{
			pid[x] = fork();
			if (pid[x] == 0)
			{
				check_for_execution_to_file(head, &status);
				free_fd(size - 1, fd);
				free(pid);
				ft_exit(head, status);
			}
			x++;
		}
		close_stdin_pipe_case(&stdin_out[0], fd, i);
		free_args(head->data.command_n_args);
		head = head->next;
		i++;
	}
	x = 0;
	while (x < size)
	{
		waitpid(pid[x], &status, 0);
		x++;
	}
	free(pid);
	free_fd(size - 1, fd);
	return (status);
}

int	execute_command(t_pipes *node)
{
	char	**args_array;
	int		cmd;

	args_array = node->data.command_n_args;
	cmd = node->data.command_type;
	if (cmd == ECHO)
		ft_echo(args_array);
	if (cmd == CD)
		return (ft_cd(node, args_array));
	if (cmd == PWD)
		ft_pwd();
	if (cmd == EXPORT)
		return (ft_export(node, args_array));
	if (cmd == UNSET)
		return (ft_unset(&node->init.envs, &node->init.sorted_envs, args_array), 0);
	if (cmd == ENV)
		return (ft_env(node->init.envs));
	if (cmd == EXIT)
		ft_exit(node, 1);
	if (cmd == NOT_BUILTIN)
		return (ft_execve(node));
	return (1);
}
