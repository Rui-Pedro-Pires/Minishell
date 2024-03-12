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

#include "../includes/minishell.h"

void	init_data(t_pipes *node);

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

int	execute_command(t_pipes *node)
{
	char	**args_array;
	int		cmd;

	args_array = node->data.command_n_args;
	cmd = node->data.command_type;
	if (cmd == ECHO)
		ft_echo(args_array);
	if (cmd == CD)
		return (ft_cd(node->init.envs, args_array));
	if (cmd == PWD)
		ft_pwd();
	if (cmd == EXPORT)
		return (ft_export(node->init.sorted_envs, args_array), 1);
	if (cmd == UNSET)
		return (ft_unset(&node->init.envs, args_array), 1);
	if (cmd == ENV)
		return (ft_env(node->init.envs), 1);
	if (cmd == EXIT)
		ft_exit(node);
	if (cmd == NOT_BUILTIN)
		return (ft_execve(node));
	return (1);
}

int	list_iterator_executer(t_pipes *head)
{
	int	fd;
	int	status;
	int	save_stdout;

	while (head)
	{
		init_data(head);
		if (head->in_out.output_type == REDIRECT_OUTPUT || \
			head->in_out.output_type == APPEND_OUTPUT)
		{
			fd = open(head->in_out.output_file, O_APPEND | O_WRONLY);
			if (fd < 0)
			{
				free_args(head->data.command_n_args);
				return (perror("minishell"), 0);
			}
			save_stdout = dup(STDOUT_FILENO);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			status = execute_command(head);
			if ((status == 0 && head->pipe_type == D_PIPE) || status == 0)
			{
				dup2(save_stdout, 1);
				close(save_stdout);
				free_args(head->data.command_n_args);
				return (0);
			}
			dup2(save_stdout, 1);
			close(save_stdout);
		}
		else
		{
			status = execute_command(head);
			if ((status == 0 && head->pipe_type == D_PIPE) || status == 0)
			{
				free_args(head->data.command_n_args);
				return (0);
			}
		}
		free_args(head->data.command_n_args);
		head = head->next;
	}
	return (1);
}

void	init_data(t_pipes *node)
{
	node->in_out.input_type = NO_INPUT;
	node->in_out.output_type = NO_OUTPUT;
	node->in_out.output_file = NULL;
	node->in_out.input_file = NULL;
	define_input_and_output(node);
	node->data.command_n_args = ft_split(node->input_string, ' ');
	command_decider(node);
}
