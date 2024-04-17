/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 09:47:46 by jorteixe          #+#    #+#             */
/*   Updated: 2024/03/26 11:42:40 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*add_rest_of_array(char **array);

t_envs	*create_env_node(char *env_var, bool shlvl_to_change)
{
	t_envs	*node;
	char	**temp_array;

	if (shlvl_to_change)
		shlvl_change(&env_var);
	node = malloc(sizeof(t_envs));
	if (!node)
		return (NULL);
	node->whole_str = ft_strdup(env_var);
	if (ft_strchr(node->whole_str, '='))
		node->has_equal = true;
	else
		node->has_equal = false;
	temp_array = ft_split(env_var, '=');
	node->name = ft_strdup(temp_array[0]);
	if (temp_array[1])
		node->value = add_rest_of_array(temp_array);
	else
		node->value = ft_strdup("");
	free_split_array(temp_array);
	node->next = NULL;
	return (node);
}

t_envs	*create_env_list(char **env, bool shlvl_to_change)
{
	t_envs	*head;
	t_envs	*current;
	t_envs	*prev;

	head = NULL;
	prev = NULL;
	while (*env)
	{
		current = create_env_node(*env, shlvl_to_change);
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
			if (ft_strcmp(current->whole_str, current->next->whole_str) > 0)
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

char	*add_rest_of_array(char **array)
{
	char	*str;
	int		i;

	i = 2;
	str = ft_strdup(array[1]);
	while (array[i])
	{
		str = ft_strjoin_free(str, "=");
		str = ft_strjoin_free(str, array[i]);
		i++;
	}
	return (str);
}
