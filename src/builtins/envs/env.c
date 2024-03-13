/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:21:27 by jorteixe          #+#    #+#             */
/*   Updated: 2024/02/16 14:21:37 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_env(t_envs *head) //#TODO Return EXIT_FAILURE or EXIT_SUCCESS
{
	t_envs	*current;

	current = head;
	while (current != NULL)
	{
		printf("Name: %s, Value: %s\n", current->name, current->value);
		current = current->next;
	}
	printf("\n" RESET);
	return(EXIT_SUCCESS);
}
