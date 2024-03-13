/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:35:59 by jorteixe          #+#    #+#             */
/*   Updated: 2024/02/26 10:35:59 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_execve(t_pipes *node)
{
	if (ft_strchr(node->data.command_n_args[0], '/'))
		return (executens_ve(node));
	else
		return (create_path_to_execve(node));
}

int	executens_ve(t_pipes *node)
{
	char	**env_array;
	int		status;
	int		checker;

	env_array = NULL;
	checker = 0;
	status = 0;
	if (node->in_out.input_type == HEARDOC)
	{
		return (read_from_heardoc(node, \
			node->init.heardocs[node->init.heardoc_index]));
	}
	else if (node->in_out.input_type == REDIRECT_INPUT)
	{
		if (!redirect_input_case(node))
			return (0);
		return (read_from_stdin(node, node->in_out.data_read));
	}
	else
		return (normal_executer(node, env_array, status, checker));
	return (1);
}

int	normal_executer(t_pipes *node, char **env_array, int status, int checker)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (error_handler(ERR_FORK, NULL, NULL), 0);
	else if (pid == 0)
	{
		env_array = envlist_to_array(node->init.envs);
		status = execve(node->data.command_n_args[0],
				node->data.command_n_args, env_array);
		if (status == -1)
		{
			if (errno == ENOENT)
				printf("%s: Command not found\n",
					node->data.command_n_args[0]);
			else
				perror("execve");
			free_args(env_array);
			ft_exit(node, 0);
		}
	}
	waitpid(pid, &checker, 0);
	if (checker != 0)
		return (0);
	return (1);
}
