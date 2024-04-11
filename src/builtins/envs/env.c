/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:21:27 by jorteixe          #+#    #+#             */
/*   Updated: 2024/03/26 11:34:25 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_env(t_envs *head)
{
	t_envs	*current;

	current = head;
	while (current != NULL)
	{
		if (current->value && current->has_equal)
			printf("%s=%s\n", current->name, current->value);
		if (!current->value && current->has_equal)
			printf("%s= \n", current->name);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
