/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:38:09 by jorteixe          #+#    #+#             */
/*   Updated: 2024/03/26 10:26:22 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool str_is_number(char *str);
void print_error(char *str);

void	ft_exit(t_pipes *head, int exit_type, char **args_array)
{
	if (args_array[2] != NULL)
	{
		exit_type = 1;
		print_error(" too many arguments");
	}
	else if (args_array[1] != NULL)
	{
		int number = atoi(args_array[1]);
		if (!str_is_number(args_array[1]))
		{
			exit_type = 2;
			print_error(" numeric argument required");
		}
		else
			exit_type = number;
	}
	free_heardoc(head);
	free_env_list(head->init.envs);
	free_env_list(head->init.sorted_envs);
	free_args(head->data.command_n_args);
	free_list(&head);
	rl_clear_history();
	exit(exit_type);
}

bool str_is_number(char *str)
{
    int i = 0;

    // Handle negative numbers
    if (str[i] == '-' || str[i] == '+')
        i++;

    // Check for non-digit characters
    for (; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
            return false;
    }

    return true;
}

void print_error(char *str)
{
	write(2, str, strlen(str));
}