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

char	*create_path_to_execve(t_pipes *node)
{
	char	*path_str;
	char	**paths_array;
	char	*temp_str;
	char	*return_str;
	int		i;

	i = 0;
	path_str = ft_getenv(node->init->envs, "PATH");
	if (path_str == NULL)
		return (0);
	paths_array = ft_split(path_str, ':');
	free(path_str);
	temp_str = ft_strdup(node->data.command_n_args[0]);
	return_str = ft_strdup(node->data.command_n_args[0]);
	paths_array[i] = ft_strjoin_free(paths_array[i], "/");
	return_str = ft_strjoin_free_v2(paths_array[i], return_str);
	while (access(return_str, F_OK) != 0 && paths_array[++i] != NULL)
	{
		paths_array[i] = ft_strjoin_free(paths_array[i], "/");
		free(return_str);
		return_str = ft_strjoin(paths_array[i], temp_str);
	}
	free(temp_str);
	free_args(paths_array);
	return (return_str);
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

void	update_env_last_arg(t_pipes *node)
{
	int		i;
	t_envs	*envs;
	char	*last_arg;

	i = 0;
	if (node->init->envs == NULL)
		return ;
	while (node->data.command_n_args[i])
		i++;
	if (i == 0)
		return ;
	last_arg = node->data.command_n_args[i - 1];
	envs = node->init->envs;
	while (envs)
	{
		if (!ft_strcmp(envs->name, "_"))
		{
			free(envs->value);
			envs->value = ft_strdup(last_arg);
			break ;
		}
		envs = envs->next;
	}
}

void	update_sorted_env_last_arg(t_pipes *node)
{
	int		i;
	t_envs	*envs;
	char	*last_arg;

	i = 0;
	if (node->init->sorted_envs == NULL)
		return ;
	while (node->data.command_n_args[i])
		i++;
	if (i == 0)
		return ;
	last_arg = node->data.command_n_args[i - 1];
	envs = node->init->sorted_envs;
	while (envs)
	{
		if (!ft_strcmp(envs->name, "_"))
		{
			free(envs->value);
			envs->value = ft_strdup(last_arg);
			break ;
		}
		envs = envs->next;
	}
}
