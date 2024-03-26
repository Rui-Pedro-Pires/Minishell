/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:33:46 by jorteixe          #+#    #+#             */
/*   Updated: 2024/02/16 14:33:46 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int		handle_unset_errors(char **str_array);

void	ft_unset(t_envs **head, t_envs **head_sorted, char **str_array)
{
	t_envs	*prev;
	t_envs	*current;

	handle_unset_errors(str_array);
	prev = find_prev_node(*head, str_array[1]);
	if (prev)
		current = prev->next;
	else
		current = *head;
	if (!current || strcmp(current->name, str_array[1]))
		return ;
	remove_node(head, prev, current);
	prev = find_prev_node(*head_sorted, str_array[1]);
	if (prev)
		current = prev->next;
	else
		current = *head_sorted;
	remove_node(head_sorted, prev, current);
}

t_envs	*find_prev_node(t_envs *head, char *str)
{
	t_envs	*current;
	t_envs	*prev;

	current = head;
	prev = NULL;
	while (current && strcmp(current->name, str))
	{
		prev = current;
		current = current->next;
	}
	return (prev);
}

void	remove_node(t_envs **head, t_envs *prev, t_envs *current)
{
	if (prev == NULL)
		*head = current->next;
	else
		prev->next = current->next;
	free_nodes(current);
}

void	free_nodes(t_envs *node)
{
	free(node->name);
	free(node->value);
	free(node->whole_str);
	free(node);
}

int	handle_unset_errors(char **str_array)
{
	if (str_array[1] == NULL)
	{
		printf("ruiolive&&jorteixe@minishell: unset: not enough arguments\n\n");
		return (EXIT_FAILURE);
	}
	if (str_array[2] != NULL)
	{
		printf("\nruiolive&&jorteixe@minishell: unset: too many arguments\n");
		return (EXIT_FAILURE);
	}
	if (ft_strcmp(str_array[1], "HOME"))
	{
		printf("Can't remove \"HOME\" from env variables.\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
