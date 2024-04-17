/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:50:15 by jorteixe          #+#    #+#             */
/*   Updated: 2024/04/11 10:50:15 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int		handle_unset_errors(char **str_array);

void	ft_unset(t_envs **head, t_envs **head_sorted, char **str_array)
{
	t_envs	*prev;
	t_envs	*current;
	int		i;

	i = 1;
	while (str_array[i] != NULL)
	{
		prev = find_prev_node(*head, str_array[i]);
		if (prev)
			current = prev->next;
		else
			current = *head;
		remove_node(head, prev, current);
		prev = find_prev_node(*head_sorted, str_array[i]);
		if (prev)
			current = prev->next;
		else
			current = *head_sorted;
		remove_node(head_sorted, prev, current);
		i++;
	}
}

t_envs	*find_prev_node(t_envs *head, char *str)
{
	t_envs	*current;
	t_envs	*prev;

	current = head;
	prev = NULL;
	while (current && ft_strcmp(current->name, str))
	{
		prev = current;
		current = current->next;
	}
	return (prev);
}

void	remove_node(t_envs **head, t_envs *prev, t_envs *current)
{
	if (current == NULL)
		return ;
	if (prev == NULL)
		*head = current->next;
	else
		prev->next = current->next;
	free_nodes(current);
}

void	free_nodes(t_envs *node)
{
	if (node == NULL)
		return ;
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
	return (EXIT_SUCCESS);
}
