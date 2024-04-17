/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:35:59 by jorteixe          #+#    #+#             */
/*   Updated: 2024/04/06 13:10:15 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		error_message_execve(t_pipes *node, char **env_array);
int		err_message_eaccess(t_pipes *node);
int		err_message_enoent(t_pipes *node);

int	executens_ve(t_pipes *node)
{
	char	**env_array;
	char	*temp_str;

	reset_signals();
	env_array = NULL;
	if (!ft_strchr(node->data.command_n_args[0], '/'))
		temp_str = create_path_to_execve(node);
	else
		temp_str = ft_strdup(node->data.command_n_args[0]);
	if (node->in_out.input_type == HEARDOC)
		write_pipe_heardoc(node);
	else if (node->in_out.input_type == REDIRECT_INPUT)
		write_pipe_stdin(node);
	if (!temp_str)
	{
		print_error("minishell: ");
		print_error(node->data.command_n_args[0]);
		print_error(": No such file or directory\n");
		return (127);
	}
	env_array = envlist_to_array(node->init->envs);
	execve(temp_str, node->data.command_n_args, env_array);
	free(temp_str);
	return (error_message_execve(node, env_array));
}

char	*create_error_str(t_pipes *node)
{
	int		i;
	int		x;
	char	*new_str;

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
	free_args(env_array);
	if (errno == ENOENT)
	{
		return (err_message_enoent(node));
	}
	if (errno == EACCES)
	{
		return (err_message_eaccess(node));
	}
	return (127);
}

int	err_message_eaccess(t_pipes *node)
{
	DIR	*dirent;

	dirent = opendir(node->data.command_n_args[0]);
	if (dirent == NULL)
	{
		print_error("minishell: ");
		print_error(node->data.command_n_args[0]);
		print_error(": Permission denied\n");
		return (126);
	}
	else
	{
		closedir(dirent);
		print_error("minishell: ");
		print_error(node->data.command_n_args[0]);
		print_error(": Is a directory\n");
		return (126);
	}
}

int	err_message_enoent(t_pipes *node)
{
	if (ft_strchr(node->data.command_n_args[0], '/'))
	{
		print_error("minishell: ");
		print_error(node->data.command_n_args[0]);
		print_error(": No such file or directory\n");
		return (127);
	}
	else
	{
		print_error(node->data.command_n_args[0]);
		print_error(": command not found\n");
		return (127);
	}
}
