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

void	ft_exit(char **heardocs, t_envs *head_envs, t_pipes *head)
{
	free_heardoc(&heardocs);
	free_list(&head);
	free_env_list(head_envs);
	rl_clear_history();
	exit(1);
}
