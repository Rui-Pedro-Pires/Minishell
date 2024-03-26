/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:17:21 by jorteixe          #+#    #+#             */
/*   Updated: 2024/03/26 18:08:20 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_process(t_pipes *head, int *fd, int i, int stdin);
void	loop_list_and_execute(t_pipes *head, int size, int *status);
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
	int	size;

	status = 0;
	size = list_size(head);
	if (size == 1)
		return (single_command(head));
	loop_list_and_execute(head, size, &status);
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
		ft_exit(node, 1, args_array);
	if (cmd == NOT_BUILTIN)
		return (ft_execve(node));
	return (0);
}

void	loop_list_and_execute(t_pipes *head, int size, int *status)
{
	int	i;
	int	stdin;
	int	fd[2];

	i = 0;
	stdin = dup(STDIN_FILENO);
	while (head)
	{
		init_data(head);
		child_process(head, fd, i, stdin);
		free_args(head->data.command_n_args);
		head = head->next;
		i++;
	}
	i = 0;
	close(stdin);
	while (i < size)
	{
		wait(status);
		i++;
	}
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
			ft_exit(head, status, NULL);
		}
		waitpid(pid, &status, 0);
	}
	return (status);
}

void	child_process(t_pipes *head, int *fd, int i, int stdin)
{
	int	pid;
	int	status;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		if (i != 0)
			dup2(stdin, STDIN_FILENO);
		if (head->pipe_type == S_PIPE)
			dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		close(stdin);
		check_for_execution_to_file(head, &status);
		ft_exit(head, status);
	}
	dup2(fd[0], stdin);
	close(fd[0]);
	close(fd[1]);
}
