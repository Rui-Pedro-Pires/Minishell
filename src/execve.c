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

int		read_from_stdin(t_pipes *head, char *to_be_read);

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
	pid_t	pid;
	char	**env_array;
	int		status;
	int		checker;

	if (node->in_out.input_type == HEARDOC)
		read_from_stdin(node, node->init.heardocs[node->init.heardoc_index]);
	else if (node->in_out.input_type == REDIRECT_INPUT)
	{
		read_from_stdin(node, node->in_out.data_read);
		free(node->in_out.data_read);
	}
	else
	{
		pid = fork();
		if (pid < 0)
			error_handler(ERR_FORK, NULL, NULL);
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
				// free_args(node->data.command_n_args);
				free_args(env_array);
				ft_exit(node);
				exit(EXIT_FAILURE);
			}
		}
		waitpid(pid, &checker, 0);
		if (checker != 0)
			return (0);
	}
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

int	read_from_stdin(t_pipes *head, char *to_be_read)
{
	int		pid1;
	int		pid2;
	int		fd_in[2];
	char	**env_array;
	int		status;

	if (pipe(fd_in))
		return (0);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(fd_in[1], STDOUT_FILENO);
		close(fd_in[0]);
		close(fd_in[1]);
		printf("%s\n", to_be_read);
		// ft_exit(head);
		exit(EXIT_SUCCESS);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fd_in[0], STDIN_FILENO);
		close(fd_in[0]);
		close(fd_in[1]);
		env_array = envlist_to_array(head->init.envs);
		status = execve(head->data.command_n_args[0], head->data.command_n_args,
				env_array);
		if (status == -1)
		{
			if (errno == ENOENT)
				perror("Command not found\n");
			else
				perror("execve");
			// ft_exit(head);
			exit(EXIT_FAILURE);
		}
		// ft_exit(head);
	}
	close(fd_in[0]);
	close(fd_in[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (1);
}
