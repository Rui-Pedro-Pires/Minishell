/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:35:59 by jorteixe          #+#    #+#             */
/*   Updated: 2024/04/05 20:17:52 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	error_message_execve(t_pipes *node, char **env_array);

int	executens_ve(t_pipes *node)
{
	char	**env_array;

	env_array = NULL;
	if (!ft_strchr(node->data.command_n_args[0], '/'))
		create_path_to_execve(node);
	if (node->in_out.input_type == HEARDOC)
		write_pipe_heardoc(node);
	else if (node->in_out.input_type == REDIRECT_INPUT)
		write_pipe_stdin(node);
	handle_reset_signals();
	env_array = envlist_to_array(node->init->envs);
	execve(node->data.command_n_args[0],
		node->data.command_n_args, env_array);
	return (error_message_execve(node, env_array));
}

char *create_error_str(t_pipes *node)
{
	int	i;
	int	x;
	char *new_str;

	i = ft_strlen(node->data.command_n_args[0]) - 1;
	x = i;
	while (i >= 0 && node->data.command_n_args[0][i] != '/')
		i--;
	new_str = ft_calloc(sizeof(char), x - i + 1);
	x = 0;
	while (node->data.command_n_args[0][i])
		new_str[x++] = node->data.command_n_args[0][++i];
	free(node->data.command_n_args[0]);
	return (new_str);
}

int	error_message_execve(t_pipes *node, char **env_array)
{
	char *path;
	free_args(env_array);
	if (errno == ENOENT)
	{
		path = ft_getenv(node->init->envs, "PATH");
		if (path != NULL)
			node->data.command_n_args[0] = create_error_str(node);
		print_error(node->data.command_n_args[0]);
		print_error(": command not found\n");
		if (path)
			free(path);
		return (127);
	}
	if (errno == EACCES)
	{
		print_error("minishell: ");
		print_error(node->data.command_n_args[0]);
		print_error(": Is a directory\n");
		return (126);
	}
	return (127);
}
