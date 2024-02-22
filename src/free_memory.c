/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:57:46 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/30 14:18:46 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	coador(t_pipes **head)
{
	t_pipes	*next;
	t_pipes *current;

	current = (*head);

	while (current)
	{
		next = current->next;
		free(current->input_string);
		free_data(current->data);
		free(current);
		current = next;
	}
}

void	freezzzz(char *input, char ***heardoc_read, t_pipes **head)
{
	int		i;
	t_pipes	*cur;

	i = 0;
	free(input);
	cur = *head;
	while (*head)
	{
		cur = (*head)->next;
		free((*head)->input_string);
		free(*head);
		*head = cur;
	}
	if (!(*heardoc_read))
		return ;
	while ((*heardoc_read)[i])
	{
		free((*heardoc_read)[i]);
		i++;
	}
	free((*heardoc_read));
	(*heardoc_read) = NULL;
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	if (data)
	{
		// if (data->path_command)
		// 	free(data->path_command);
		if (data->command_n_args)
		{
			while (data->command_n_args[i])
			{
				free(data->command_n_args[i]);
				i++;
			}
			free(data->command_n_args);
		}
		free(data);
	}
}

void	free_envs(t_envs *envs)
{
	if (envs)
	{
		struct s_envs *current = envs;
		struct s_envs *next;
		while (current)
		{
			next = current->next;
			free(current->name);
			free(current->value);
			free(current);
			current = next;
		}
	}
}
