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

static int	list_iterator(t_pipes *head);

int	executer(t_pipes *head, int recursive)
{
	int	status;

	status = 0;
	while (head)
	{
		status = recursive_down(head);
		if (status == 1 && head->pipe_type == D_PIPE)
			return (1);
	}
	if (status == 0 && recursive == 1)
			return (0);
	return (1); 
}

int	recursive_down(t_pipes *head)
{
	if (!head)
		return (1);
	if (check_for_dbpipe_dbamper(head->input_string))
		return (executer(head->down, 1));
	if (!recursive_down(head->down))
		return (0);
	if (head->skip == true)
		return (1);
	return (list_iterator(head));
}

int	execute_command(t_pipes *node) /*#TODO add 0 if error, 1 if success*/
{
	char	**args_array;
	int		cmd;

	args_array = node->data.command_n_args;
	cmd = node->data.command_type;
	if (cmd == ECHO)
		ft_echo(args_array, node);
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

static int	list_iterator(t_pipes *head)
{
	int	fd;
	int	status;
	int	save_stdout;

	while (head)
	{
		if (head->in_out.output_type == REDIRECT_OUTPUT || \
			head->in_out.output_type == APPEND_OUTPUT)
		{
			fd = open(head->in_out.output_file, O_APPEND | O_WRONLY);
			if (fd < 0)
				return (perror("minishell"), 0);
			save_stdout = dup(STDOUT_FILENO);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			status = execute_command(head);
			if ((status == 0 && head->pipe_type == D_PIPE) || status == 0)
			{
				dup2(save_stdout, 1);
				close(save_stdout);
				return (0);
			}
			dup2(save_stdout, 1);
			close(save_stdout);
		}
		else
		{
			status = execute_command(head);
			if ((status == 0 && head->pipe_type == D_PIPE) || status == 0)
				return (0);
		}
		head = head->next;
	}
	return (1);
}
