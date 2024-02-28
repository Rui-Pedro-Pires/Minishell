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
	t_pipes	*current;

	current = head;
	while (current)
	{
		execute_command(head);
		current = current->next;
	}
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
		ft_cd(head->envs, args_array);
	if (cmd == PWD)
		ft_pwd();
	if (cmd == EXPORT)
		ft_export(head->envs, args_array);
	if (cmd == UNSET)
		ft_unset(&head->envs, args_array);
	if (cmd == ENV)
		ft_env(head->envs);
	if (cmd == EXIT)
		ft_exit(head->heardocs, head->envs, head);
	if (cmd == NOT_BUILTIN)
		ft_execve(head->envs, args_array);
}
