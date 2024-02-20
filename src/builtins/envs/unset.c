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

void	ft_unset(t_envs **head, char **str_array)
{
	t_envs	*new_node;
	t_envs	*prev;
	t_envs	*current;
	char	*str;

	str = str_array[1];
	if (str_array[2] != NULL)
		printf("\nruiolive&&jorteixe@minishell: cd: too many arguments\n");
	new_node = create_env_node(str);
	if (ft_strcmp(new_node->name, "HOME"))
	{
		printf("Can't remove \"HOME\" from env variables.\n");
		free_nodes(new_node);
		return ;
	}
	prev = find_prev_node(*head, new_node->name);
	if (prev)
		current = prev->next;
	else
		current = *head;
	if (!current || strcmp(current->name, new_node->name))
	{
		printf("Node with value \"%s\" not found in the linked list.\n",
			new_node->name);
		free_nodes(new_node);
		return ;
	}
	remove_node(head, prev, current);
	free_nodes(new_node);
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
	printf("Node with value %s has been removed from the linked list.\n",
		current->name);
	free_nodes(current);
}

void	free_nodes(t_envs *node)
{
	free(node->name);
	free(node->value);
	free(node);
}
