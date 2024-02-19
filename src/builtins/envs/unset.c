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

void	ft_unset(t_envs *head, char *str)
{
	t_envs	*current;
	t_envs	*prev;
	t_envs	*new_node;

	current = head;
	prev = NULL;
	new_node = create_env_node(str);
	if (ft_strcmp(new_node->name, "HOME"))
	{
		printf("Can't remove \"HOME\" from env variables.\n");
		free(new_node);
		return ;
	}
	if (current != NULL && ft_strcmp(current->name, new_node->name))
	{
		head = current->next;
		free(current);
		return ;
	}
	while (current != NULL && !ft_strcmp(current->name, new_node->name))
	{
		prev = current;
		current = current->next;
	}
	if (current == NULL)
	{
		printf("Node with value %s not found in the linked list.\n",
			new_node->name);
		free(new_node);
		return ;
	}
	prev->next = current->next;
	free(current);
	free(new_node);
}
