/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:35:59 by jorteixe          #+#    #+#             */
/*   Updated: 2024/03/27 14:49:39 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	executens_ve(t_pipes *node)
{
	char	**env_array;
	int		status;

	env_array = NULL;
	status = 0;
	if (!ft_strchr(node->data.command_n_args[0], '/'))
		create_path_to_execve(node);
	if (node->in_out.input_type == HEARDOC)
	{
		return (read_from_heardoc(node, \
			node->init.heardocs[*node->init.heardoc_index]));
	}
	else if (node->in_out.input_type == REDIRECT_INPUT)
	{
		if (redirect_input_case(node))
			return (1);
		return (read_from_stdin(node, node->in_out.data_read));
	}
	else
		return (normal_executer(node, env_array, status));
	return (0);
}

int	normal_executer(t_pipes *node, char **env_array, int status)
{
	env_array = envlist_to_array(node->init.envs);
	status = execve(node->data.command_n_args[0],
		node->data.command_n_args, env_array);
	if (status == -1)
	{
		if (errno == ENOENT)
			perror(node->data.command_n_args[0]);
		else
			perror("execve");
		free_args(env_array);
		return(127);
	}
	return (0);
}

// void	error_message_execve(t_pipes *node)
// {
	
// }
