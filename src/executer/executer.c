/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:17:21 by jorteixe          #+#    #+#             */
/*   Updated: 2024/02/22 15:17:21 by jorteixe         ###   ########.fr       */
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
		if (status == 1 && head->pipe_type == D_PIPE)
		{
			while (head && head->pipe_type != AMPER)
				head = head->next;
		}
		if (head)
			head = head->next;
	}
	if (status == 0 && recursive == 1)
		return (0);
	return (1);
}

int	recursive_down(t_pipes *head)
{
	int	status;

	if (!head)
		return (2);
	if (check_for_dbpipe_dbamper(head->input_string))
		return (recursive_executer(head->down, 1));
	status = recursive_down(head->down);
	if (status == 0)
		return (0);
	else if (status == 1)
		return (1);
	return (list_iterator_executer(head));
}

int	list_iterator_executer(t_pipes *head)
{
	int	status;
	int	save_stdout;
	int	stdout;
	int	stdin;
	int	i;
	int	fd[2];

	pipe(fd);
	stdout = 0;
	stdin = 0;
	i = 0;
	status = 0;
	save_stdout = 0;
	while (head)
	{
		init_data(head);
		if (i != 0)
		{
			stdin = dup(STDIN_FILENO);
			dup2(fd[0], STDIN_FILENO);
		}
		if (head->pipe_type != S_PIPE)
		{
			close(fd[1]);
			dup2(stdout, STDOUT_FILENO);
			close(stdout);
		}
		if (head->pipe_type == S_PIPE)
		{
			stdout = dup(STDOUT_FILENO);
			dup2(fd[1], STDOUT_FILENO);
		}
		if (head->in_out.output_type == REDIRECT_OUTPUT || \
			head->in_out.output_type == APPEND_OUTPUT)
			execute_to_file(head, status, save_stdout);
		else
			execute_to_stdout(head, status);
		if (i != 0)
		{
			close(fd[0]);
			dup2(stdin, STDIN_FILENO);
			close(stdin);
		}
		head = head->next;
		i++;
	}
	return (1);
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
		return (ft_export(node, args_array), 1);
	if (cmd == UNSET)
		return (ft_unset(&node->init.envs, &node->init.sorted_envs, args_array), 1);
	if (cmd == ENV)
		return (ft_env(node->init.envs), 1);
	if (cmd == EXIT)
		ft_exit(node, 1);
	if (cmd == NOT_BUILTIN)
		return (ft_execve(node));
	return (1);
}
