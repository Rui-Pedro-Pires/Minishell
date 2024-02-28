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

#include "../includes/minishell.h"

void	ft_execve(t_envs *envs, char **args_array)
{
	char	*path_str;
	char	**paths_array;
	char	*temp_str;
	int		i;

	if (access(args_array[0], F_OK) == 0)
		executens_ve(envs, args_array);
	else
	{
		path_str = ft_getenv(envs, "PATH");
		paths_array = ft_split(path_str, ':');
		i = 0;
		temp_str = ft_strdup(args_array[0]);
		paths_array[i] = ft_strjoin(paths_array[i], "/");
		args_array[0] = ft_strjoin(paths_array[i], args_array[0]);
		while (access(args_array[0], F_OK) != 0 && paths_array[i] != NULL)
		{
			paths_array[i] = ft_strjoin(paths_array[i], "/");
			args_array[0] = ft_strjoin(paths_array[i], temp_str);
			i++;
		}
		executens_ve(envs, args_array);
	}
}

void	executens_ve(t_envs *envs, char **args_array)
{
	pid_t	pid;
	char	**env_array;
	int		status;

	pid = fork();
	if (pid < 0)
		error_handler(ERR_FORK, NULL, NULL);
	else if (pid == 0)
	{
		env_array = envlist_to_array(envs);
		status = execve(args_array[0], args_array, env_array);
		if (status == -1)
		{
			if (errno == ENOENT)
				printf("Command not found\n");
			else
				perror("execve");
		}
		// free_pnts((void**)env_array);
	}
	waitpid(pid, NULL, 0);
}

char	**envlist_to_array(t_envs *envs)
{
	char	**env_array;
	t_envs	*current;
	int		i;

	current = envs;
	env_array = malloc(listlen(envs) + 1);
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
