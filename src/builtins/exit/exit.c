/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:38:09 by jorteixe          #+#    #+#             */
/*   Updated: 2024/02/21 13:38:09 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_exit(t_pipes *head)
{
	
	free_heardoc(head);
	free_env_list(head->init.envs);
	free_env_list(head->init.sorted_envs);
	free_list(&head);
	// printf("exit\n");
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
