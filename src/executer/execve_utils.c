/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:26:59 by ruiolive          #+#    #+#             */
/*   Updated: 2024/04/02 15:26:23 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_path_to_execve(t_pipes *node)
{
	char	*path_str;
	char	**paths_array;
	char	*temp_str;
	int		i;

	path_str = ft_getenv(node->init->envs, "PATH");
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
