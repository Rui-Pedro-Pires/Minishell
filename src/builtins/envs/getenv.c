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

char	*ft_getenv(t_envs *head, char *str)
{
	t_envs	*current;

	current = head;
	while (current != NULL)
	{
		if (!ft_strcmp(current->name, str))
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (NULL);
}
