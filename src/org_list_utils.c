/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   org_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:47:25 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/23 13:47:25 by jorteixe         ###   ########.fr       */
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

int	fill_data(t_pipes *pipe_struct, int count)
{
	int		i;
	int 	back;
	int		front;
	t_data	*data;

	data = pipe_struct->data;
	if (pipe_struct->input_string == NULL /*check if its only spaces*/)
		return ((pipe_struct->empty_node = true), 1);
	else
		pipe_struct->empty_node = false;
	i = 0;
	front = 0;
	while (i < count)
	{
		prepare_split(&data[i], pipe_struct, &back, &front);
		// data[i].command_n_args = ft_special_split(pipe_struct->input_string,
				32);
		i++;
	}
}
