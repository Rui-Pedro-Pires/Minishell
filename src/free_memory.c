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

// void	coador(t_pipes **head)
// {
// 	t_pipes	*next;
// 	t_pipes *current;

// 	current = (*head);

// 	while (current)
// 	{
// 		next = current->next;
// 		free(current->input_string);
// 		free_data(current->data);
// 		free(current);
// 		current = next;
// 	}
// }

void	free_input(char **input)
{
	free(*input);
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

void	free_list(t_pipes **head)
{
	if (!(*head))
		return ;
	free_list(&(*head)->down);
	free_list(&(*head)->next);
	free((*head)->input_string);
	free(*head);
	*head = NULL;
}