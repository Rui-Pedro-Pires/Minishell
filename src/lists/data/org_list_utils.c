/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   org_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:47:25 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/25 09:33:50 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	command_decider1(t_pipes *head, int status)
{
	if (status == 1 || check_for_dbpipe_dbamper(head->input_string))
	{
		head->skip = true;
		return (-1);
	}
	if (!head->data.command_n_args[0])
	{
		head->data.command_type = NO_COMMAND;
		return (-1);
	}
	if (ft_strncmp(head->data.command_n_args[0], "echo", 5) == 0 \
		|| ft_strncmp(head->data.command_n_args[0], "\"echo\"", 7) == 0 \
		|| ft_strncmp(head->data.command_n_args[0], "\'echo\'", 7) == 0)
		head->data.command_type = ECHO;
	else if (ft_strncmp(head->data.command_n_args[0], "cd", 3) == 0 \
		|| ft_strncmp(head->data.command_n_args[0], "\"cd\"", 5) == 0 \
		|| ft_strncmp(head->data.command_n_args[0], "\'cd\'", 5) == 0)
		head->data.command_type = CD;
	else if (ft_strncmp(head->data.command_n_args[0], "pwd", 4) == 0 \
		|| ft_strncmp(head->data.command_n_args[0], "\"pwd\"", 6) == 0 \
		|| ft_strncmp(head->data.command_n_args[0], "\'pwd\'", 6) == 0)
		head->data.command_type = PWD;
	else if (ft_strncmp(head->data.command_n_args[0], "export", 7) == 0 \
		|| ft_strncmp(head->data.command_n_args[0], "\"export\"", 9) == 0 \
		|| ft_strncmp(head->data.command_n_args[0], "\'export\'", 9) == 0)
		head->data.command_type = EXPORT;
	else
		return (0);
	return (1);
}
