/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:38:09 by jorteixe          #+#    #+#             */
/*   Updated: 2024/04/06 11:58:03 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_error(char *str);
void	free_resources(t_pipes *head);
void	handle_too_many_args(int *exit_type);
void	handle_numeric_arg(int *exit_type, char *arg);

void	ft_exit(t_pipes *head, int exit_type, char **args_array)
{
	int	i;

	i = 0;
	if (args_array == NULL)
	{
		free_resources(head);
		exit(exit_type);
	}
	while (args_array[i] != NULL)
		i++;
	if (2 < i && args_array[2] != NULL)
		handle_too_many_args(&exit_type);
	else if (1 < i && args_array[1] != NULL)
		handle_numeric_arg(&exit_type, args_array[1]);
	free_resources(head);
	exit(exit_type);
}

bool	ft_str_is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (!isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	print_error(char *str)
{
	write(2, str, ft_strlen(str));
}

void	print_error_char(char str)
{
	write(2, &str, 1);
}
