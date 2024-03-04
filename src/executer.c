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

void	executer(t_pipes *head)
{
	int	fd;
	int	save_stdout;

	if (!head)
		return ;
	executer(head->down);
	executer(head->next);
	if (!define_in_out(head))
		return ;
	if (head->in_out.output_type == REDIRECT_OUTPUT || \
		head->in_out.output_type == APPEND_OUTPUT)
	{
		fd = open(head->in_out.output_file, O_APPEND | O_WRONLY);
		save_stdout = dup(STDOUT_FILENO);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		execute_command(head);
		dup2(save_stdout, 1);
		close(save_stdout);
	}
	else
		execute_command(head);
}

void	execute_command(t_pipes *node) /*#TODO add 0 if error, 1 if success*/
{
	char	**args_array;
	int		cmd;

	args_array = node->data.command_n_args;
	cmd = node->data.command_type;
	if (cmd == ECHO)
		ft_echo(args_array);
	if (cmd == CD)
		ft_cd(node->init.envs, args_array);
	if (cmd == PWD)
		ft_pwd();
	if (cmd == EXPORT)
		ft_export(node->init.envs, args_array);
	if (cmd == UNSET)
		ft_unset(&node->init.envs, args_array);
	if (cmd == ENV)
		ft_env(node->init.envs);
	if (cmd == EXIT)
		ft_exit(node);
	if (cmd == NOT_BUILTIN)
		ft_execve(node);
}
