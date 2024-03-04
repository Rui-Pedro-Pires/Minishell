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
	int		pid;
	
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		current = head;
		while (current != NULL)
		{
			printf("Name: %s, Value: %s\n", current->name, current->value);
			current = current->next;
		}
		printf("\n"RESET);
	}
	waitpid(pid, NULL, 0);
}
