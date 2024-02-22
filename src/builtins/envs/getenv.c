/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:39:36 by jorteixe          #+#    #+#             */
/*   Updated: 2024/02/21 10:39:36 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*ft_getenv(t_envs *head, char *str)
{
	t_envs	*current;

	current = head;
	while (current != NULL)
	{
		if (ft_strcmp(current->name, str))
			return (ft_strdup(current->value));
		current = current->next;
	}
	return ("");
}
