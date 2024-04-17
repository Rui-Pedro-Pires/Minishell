/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:13:13 by jorteixe          #+#    #+#             */
/*   Updated: 2024/04/11 11:13:13 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_resources(t_pipes *head)
{
	free_heardoc(head);
	free_env_list(head->init->envs);
	free_env_list(head->init->sorted_envs);
	if (head->init->pid)
	{
		free(head->init->pid);
		head->init->pid = NULL;
	}
	free_list(&head);
	rl_clear_history();
}

void	handle_too_many_args(int *exit_type)
{
	*exit_type = 1;
	print_error("\nruiolive&&jorteixe@minishell: exit: too many arguments\n");
}

void	handle_numeric_arg(int *exit_type, char *arg)
{
	int	number;

	number = ft_atoi(arg);
	if (!ft_str_is_number(arg))
	{
		*exit_type = 2;
		print_error("\nruiolive&&jorteixe@minishell: exit: ");
		print_error(arg);
		print_error(": numeric argument required\n");
	}
	else
		*exit_type = number;
}
