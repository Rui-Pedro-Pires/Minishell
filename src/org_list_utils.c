/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   org_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:47:25 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/24 12:09:54 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_input(t_pipes *pipe)
{
	char	*str;
	int		count;

	count = 1;
	str = pipe->input_string;
	count += count_larrow(str);
	count += count_rarrow(str);
	count += count_amperz(str);
	return (count);
}

int	count_larrow(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
		{
			count++;
			if (str[i + 1] == '<')
				i++;
		}
		i++;
	}
	return (count);
}

int	count_rarrow(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '>')
		{
			count++;
			if (str[i + 1] == '>')
				i++;
		}
		i++;
	}
	return (count);
}

int	count_amperz(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '&' && str[i + 1] == '&')
			count++;
		i++;
	}
	return (count);
}

// int	fill_data(t_pipes *pipe_struct, int count)
// {
// 	int		i;
// 	t_data	*data;

// 	data = pipe_struct->data;
// 	if (pipe_struct->input_string == NULL)
// 		return ((pipe_struct->empty_node = true), 1);
// 	else
// 		pipe_struct->empty_node = false;
// 	i = 0;
// 	while (i < count)
// 	{
// 		data[i].command_n_args = ft_special_split(pipe_struct->input_string,
// 				32);
// 	}
// }







void	command_decider(t_data *data)
{
	if (ft_strncmp(data->command_n_args[0], "echo", 5) == 0 \
	|| ft_strncmp(data->command_n_args[0], "\"echo\"", 7) == 0)
		data->command_type = ECHO;
	else if (ft_strncmp(data->command_n_args[0], "cd", 3) == 0 \
	|| ft_strncmp(data->command_n_args[0], "\"cd\"", 5) == 0)
		data->command_type = CD;
	else if (ft_strncmp(data->command_n_args[0], "pwd", 4) == 0 \
	|| ft_strncmp(data->command_n_args[0], "\"pwd\"", 6) == 0)
		data->command_type = PWD;
	else if (ft_strncmp(data->command_n_args[0], "export", 7) == 0 \
	|| ft_strncmp(data->command_n_args[0], "\"export\"", 9) == 0)
		data->command_type = EXPORT;
	else if (ft_strncmp(data->command_n_args[0], "unset", 6) == 0 \
	|| ft_strncmp(data->command_n_args[0], "\"unset\"", 8) == 0)
		data->command_type = UNSET;
	else if (ft_strncmp(data->command_n_args[0], "env", 4) == 0 \
	|| ft_strncmp(data->command_n_args[0], "\"env\"", 6) == 0)
		data->command_type = ENV;
	else if (ft_strncmp(data->command_n_args[0], "exit", 5) == 0 \
	|| ft_strncmp(data->command_n_args[0], "\"exit\"", 7) == 0)
		data->command_type = EXIT;
	else
		data->command_type = NOT_BUILTIN;
}
