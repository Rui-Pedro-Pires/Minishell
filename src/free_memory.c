/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:57:46 by ruiolive          #+#    #+#             */
/*   Updated: 2024/03/26 10:28:32 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	args = NULL;
}

void	free_input(char **input)
{
	if (!(*input))
		return ;
	free(*input);
	*input = NULL;
}

void	free_heardoc(t_pipes *head)
{
	int	i;

	i = 0;
	if (!head || !(head->init->heardocs))
		return ;
	while (head->init->heardocs[i])
	{
		free(head->init->heardocs[i]);
		i++;
	}
	free(head->init->heardocs);
	head->init->heardocs = NULL;
}

void	free_envs(t_envs *envs)
{
	struct s_envs	*current;
	struct s_envs	*next;

	if (envs)
	{
		current = envs;
		while (current)
		{
			next = current->next;
			free(current->name);
			free(current->value);
			free(current);
			current = next;
		}
	}
	envs = NULL;
}

void	free_list(t_pipes **head)
{
	if (!(*head))
		return ;
	if ((*head)->init->pid)
	{
		free((*head)->init->pid);
		(*head)->init->pid = NULL;
	}
	free_list(&(*head)->down);
	free_list(&(*head)->next);
	free_args((*head)->data.command_n_args);
	(*head)->data.command_n_args = NULL;
	free((*head)->input_string);
	free(*head);
	*head = NULL;
}
