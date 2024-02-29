/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 09:47:46 by jorteixe          #+#    #+#             */
/*   Updated: 2024/02/16 09:47:46 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// int	main(int argc, char const **argv, char **env)
// {

//     (void)argv;
//     (void)argc;
//
//     ft_env(head);
// 	free_env_list(head);
//     return (0);
// }

t_envs	*create_env_node(char *env_var)
{
	t_envs	*node;
	char	**temp_array;

	node = malloc(sizeof(t_envs));
	if (!node)
		return (NULL);
	node->whole_str = env_var;
	temp_array = ft_split(env_var, '=');
	node->name = ft_strdup(temp_array[0]);
	if (temp_array[1])
		node->value = ft_strdup(temp_array[1]);
	else
		node->value = NULL;
	free_split_array(temp_array);
	node->next = NULL;
	return (node);
}

t_envs	*create_env_list(char **env)
{
	t_envs	*head;
	t_envs	*current;
	t_envs	*prev;

	head = NULL;
	prev = NULL;
	while (*env)
	{
		current = create_env_node(*env);
		if (!head)
			head = current;
		else
			prev->next = current;
		prev = current;
		env++;
	}
	return (head);
}
t_envs	*swap_nodes(t_envs *prev, t_envs *current, t_envs *next_node)
{
	if (prev == NULL)
	{
		current->next = next_node->next;
		next_node->next = current;
		return (next_node);
	}
	else
	{
		prev->next = next_node;
		current->next = next_node->next;
		next_node->next = current;
	}
	return (current);
}

t_envs	*bubble_sort(t_envs *head)
{
	t_envs	*current;
	t_envs	*prev;
	int		swapped;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = head;
		prev = NULL;
		while (current && current->next)
		{
			if (strcmp(current->whole_str, current->next->whole_str) > 0)
			{
				swapped = 1;
				current = swap_nodes(prev, current, current->next);
				if (prev == NULL)
					head = current;
			}
			prev = current;
			current = current->next;
		}
	}
	return (head);
}