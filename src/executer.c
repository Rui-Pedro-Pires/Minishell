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
	if (!head)
		return ;
	executer(head->down);
	executer(head->next);
	// head->input = define_input();
	// head->output = define_output();
	execute_command(head);
}

void	execute_command(t_pipes *head) /*#TODO add 0 if error, 1 if success*/
{
	char	**args_array;
	int		cmd;

	args_array = head->data.command_n_args;
	cmd = head->data.command_type;
	if (cmd == ECHO)
		ft_echo(args_array);
	if (cmd == CD)
		ft_cd(head->init.envs, args_array);
	if (cmd == PWD)
		ft_pwd();
	if (cmd == EXPORT)
		ft_export(head->init.sorted_envs, args_array);
	if (cmd == UNSET)
		ft_unset(&head->init.envs, args_array);
	if (cmd == ENV)
		ft_env(head->init.envs);
	if (cmd == EXIT)
		ft_exit(head);
	if (cmd == NOT_BUILTIN)
		ft_execve(head->init.envs, args_array);
}
