/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:17:21 by jorteixe          #+#    #+#             */
/*   Updated: 2024/03/26 15:18:06 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	loop_list_and_execute(t_pipes *head, int size, int *status, t_pipe_memmory pipe_mem);
int		pipe_execute(t_pipes *head, int i);
int		single_command(t_pipes *head);

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
	int	status;
	t_pipe_memmory pipe_mem;

	status = 0;
	pipe_mem.size = list_size(head);
	if (pipe_mem.size == 1)
		return (single_command(head));
	pipe_mem.fd = alloc_memory_for_fd(pipe_mem.size - 1);
	pipe_mem.pid = malloc(sizeof(int) * pipe_mem.size);
	loop_list_and_execute(head, pipe_mem.size, &status, pipe_mem);
	free_pipe_mem(pipe_mem);
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
	return (0);
}

void	loop_list_and_execute(t_pipes *head, int size, int *status, t_pipe_memmory pipe_mem)
{
	int	i;
	int	stdin;
	int	stdout;

	i = 0;
	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	while (head)
	{
		head->pipe_memmory = pipe_mem;
		change_stdout_pipe_case(head, &stdout, i);
		change_stdin_pipe_case(head, i);
		init_data(head);
		pipe_execute(head, i);
		close_stdin_pipe_case(head, i);
		free_args(head->data.command_n_args);
		head = head->next;
		i++;
	}
	i = 0;
	while (i < size)
	{
		waitpid(pipe_mem.pid[i], status, 0);
		i++;
	}
	dup2(stdin, STDIN_FILENO);
	close(stdin);
}

int	pipe_execute(t_pipes *head, int i)
{
	int	status;

	status = 0;
	head->pipe_memmory.pid[i] = fork();
	if (head->pipe_memmory.pid[i] == 0)
	{
		// close(head->pipe_memmory.fd[i][0]);
		// close(head->pipe_memmory.fd[i][1]);
		check_for_execution_to_file(head, &status);
		free_pipe_mem(head->pipe_memmory);
		ft_exit(head, status);
	}
	return (status);
}

int	single_command(t_pipes *head)
{
	int	status;
	int	pid;

	init_data(head);
	if (head->data.command_type != NOT_BUILTIN)
		check_for_execution_to_file(head, &status);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			check_for_execution_to_file(head, &status);
			ft_exit(head, status);
		}
		waitpid(pid, &status, 0);
	}
	return (status);
}
