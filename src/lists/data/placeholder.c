/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placeholder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/29 11:54:26 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	command_decider2(t_data data)
{
	if (!data.command_n_args[0])
	{
		data.command_type = NO_COMMAND;
		return (-1);
	}
	if (ft_strncmp(data.command_n_args[0], "unset", 6) == 0
		|| ft_strncmp(data.command_n_args[0], "\"unset\"", 8) == 0
		|| ft_strncmp(data.command_n_args[0], "\'unset\'", 8) == 0)
		data.command_type = UNSET;
	else if (ft_strncmp(data.command_n_args[0], "env", 4) == 0
		|| ft_strncmp(data.command_n_args[0], "\"env\"", 6) == 0
		|| ft_strncmp(data.command_n_args[0], "\'env\'", 6) == 0)
		data.command_type = ENV;
	else if (ft_strncmp(data.command_n_args[0], "exit", 5) == 0
		|| ft_strncmp(data.command_n_args[0], "\"exit\"", 7) == 0
		|| ft_strncmp(data.command_n_args[0], "\'exit\'", 7) == 0)
		data.command_type = EXIT;
	else
		return (0);
	return (1);
}

int	check_only_spaces(char *input_str)
{
	int	i;

	i = 0;
	while (input_str[i] && (input_str[i] == ' ' || input_str[i] == '\t'
			|| input_str[i] == '\n'))
		i++;
	if (input_str[i])
		return (0);
	return (1);
}

int	word_counter(char const *s, char c, int size)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i] && i < size)
	{
		while (s[i] == c && s[i])
		{
			i++;
		}
		if (s[i])
		{
			counter++;
		}
		while (s[i] != c && s[i])
		{
			i++;
		}
	}
	return (counter);
}

void	organize_list(t_pipes *head)
{
	if (!head)
		return ;
	organize_list(head->down);
	organize_list(head->next);
	fill_data(head);
}
