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

int	command_decider2(t_data *data)
{
	if (ft_strncmp(data->command_n_args[0], "unset", 6) == 0
		|| ft_strncmp(data->command_n_args[0], "\"unset\"", 8) == 0
		|| ft_strncmp(data->command_n_args[0], "\'unset\'", 8) == 0)
		data->command_type = UNSET;
	else if (ft_strncmp(data->command_n_args[0], "env", 4) == 0
		|| ft_strncmp(data->command_n_args[0], "\"env\"", 6) == 0
		|| ft_strncmp(data->command_n_args[0], "\'env\'", 6) == 0)
		data->command_type = ENV;
	else if (ft_strncmp(data->command_n_args[0], "exit", 5) == 0
		|| ft_strncmp(data->command_n_args[0], "\"exit\"", 7) == 0
		|| ft_strncmp(data->command_n_args[0], "\'exit\'", 7) == 0)
		data->command_type = EXIT;
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

int	word_counter(char const *s, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
		{
			i++;
		}
		if (s[i] != '\0')
		{
			counter++;
		}
		while (s[i] != c && s[i] != '\0')
		{
			i++;
		}
	}
	return (counter);
}

void	organize_list(t_pipes *pipe_struct)
{
	int	count;

	count = 0;
	while (pipe_struct != NULL)
	{
		count = count_input(pipe_struct);
		pipe_struct->data = malloc(sizeof(t_data) * (count + 1));
		fill_data(pipe_struct, count);
		pipe_struct = pipe_struct->next;
	}
}
