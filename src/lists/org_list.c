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

#include "../../includes/minishell.h"

static void	command_decider(t_pipes *node, int status);
static void	command_decider1(t_pipes *head);
static void	command_decider2(t_pipes *head);

void	organize_list(t_pipes *node, int status)
{
	if (!node)
		return ;
	if (check_for_dbpipe_dbamper(node->input_string))
		organize_list(node->down, 1);
	else
		organize_list(node->down, 0);
	organize_list(node->next, status);
	node->in_out.input_type = NO_INPUT;
	node->in_out.output_type = NO_OUTPUT;
	node->in_out.output_file = NULL;
	node->in_out.input_file = NULL;
	define_input_and_output(node);
	node->data.command_n_args = ft_split(node->input_string, ' ');
	command_decider(node, status);
}

static void	command_decider(t_pipes *node, int status)
{
	if (status == 1 || check_for_dbpipe_dbamper(node->input_string))
		node->skip = true;
	else if (!node->data.command_n_args[0])
		node->data.command_type = NO_COMMAND;
	else
	{
		command_decider1(node);
		command_decider2(node);
	}
}

static void	command_decider1(t_pipes *node)
{
	if (ft_strncmp(node->data.command_n_args[0], "echo", 5) == 0 \
		|| ft_strncmp(node->data.command_n_args[0], "\"echo\"", 7) == 0 \
		|| ft_strncmp(node->data.command_n_args[0], "\'echo\'", 7) == 0)
		node->data.command_type = ECHO;
	else if (ft_strncmp(node->data.command_n_args[0], "cd", 3) == 0 \
		|| ft_strncmp(node->data.command_n_args[0], "\"cd\"", 5) == 0 \
		|| ft_strncmp(node->data.command_n_args[0], "\'cd\'", 5) == 0)
		node->data.command_type = CD;
	else if (ft_strncmp(node->data.command_n_args[0], "pwd", 4) == 0 \
		|| ft_strncmp(node->data.command_n_args[0], "\"pwd\"", 6) == 0 \
		|| ft_strncmp(node->data.command_n_args[0], "\'pwd\'", 6) == 0)
		node->data.command_type = PWD;
	else if (ft_strncmp(node->data.command_n_args[0], "export", 7) == 0 \
		|| ft_strncmp(node->data.command_n_args[0], "\"export\"", 9) == 0 \
		|| ft_strncmp(node->data.command_n_args[0], "\'export\'", 9) == 0)
		node->data.command_type = EXPORT;
	else
		node->data.command_type = NOT_BUILTIN;
}

static void	command_decider2(t_pipes *node)
{
	if (ft_strncmp(node->data.command_n_args[0], "unset", 6) == 0
		|| ft_strncmp(node->data.command_n_args[0], "\"unset\"", 8) == 0
		|| ft_strncmp(node->data.command_n_args[0], "\'unset\'", 8) == 0)
		node->data.command_type = UNSET;
	else if (ft_strncmp(node->data.command_n_args[0], "env", 4) == 0
		|| ft_strncmp(node->data.command_n_args[0], "\"env\"", 6) == 0
		|| ft_strncmp(node->data.command_n_args[0], "\'env\'", 6) == 0)
		node->data.command_type = ENV;
	else if (ft_strncmp(node->data.command_n_args[0], "exit", 5) == 0
		|| ft_strncmp(node->data.command_n_args[0], "\"exit\"", 7) == 0
		|| ft_strncmp(node->data.command_n_args[0], "\'exit\'", 7) == 0)
		node->data.command_type = EXIT;
	else
		node->data.command_type = NOT_BUILTIN;
}
