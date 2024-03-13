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
	char	*path_str;
	char	**paths_array;
	char	*temp_str;
	int		i;

	if (access(node->data.command_n_args[0], F_OK) == 0)
		return (executens_ve(node));
	else
	{
		path_str = ft_getenv(node->init.envs, "PATH");
		paths_array = ft_split(path_str, ':');
		free(path_str);
		i = 0;
		temp_str = ft_strdup(node->data.command_n_args[0]);
		paths_array[i] = ft_strjoin_free(paths_array[i], "/");
		node->data.command_n_args[0] = ft_strjoin_free_v2(paths_array[i],
				node->data.command_n_args[0]);
		while (access(node->data.command_n_args[0], F_OK) != 0
			&& paths_array[i] != NULL)
		{
			paths_array[i] = ft_strjoin_free(paths_array[i], "/");
			free(node->data.command_n_args[0]);
			node->data.command_n_args[0] = ft_strjoin(paths_array[i], temp_str);
			i++;
		}
		free(temp_str);
		free_args(paths_array);
		return (executens_ve(node));
	}
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

char	**envlist_to_array(t_envs *envs)
{
	char	**env_array;
	t_envs	*current;
	int		i;

	current = envs;
	env_array = malloc(sizeof(char *) * (listlen(envs) + 1));
	i = 0;
	while (current != NULL)
	{
		env_array[i] = ft_strdup(current->whole_str);
		i++;
		current = current->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

int	listlen(t_envs *envs)
{
	t_envs	*current;
	int		len;

	len = 0;
	current = envs;
	while (current != NULL)
	{
		len++;
		current = current->next;
	}
	return (len);
}
