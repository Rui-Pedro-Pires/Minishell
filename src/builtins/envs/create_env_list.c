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
