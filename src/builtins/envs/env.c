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

void	ft_env(t_envs *head)
{
	t_envs	*current;

	current = head;
	while (current != NULL)
	{
		printf("%s", current->whole_str);
		printf("\n"RESET);
		current = current->next;
	}
}
