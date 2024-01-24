/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/24 11:01:56 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prepare_split(t_data *data, t_pipes *pipe, int *back, int *front)
{
	char	*og_str;

	og_str = pipe->input_string;
	*back = *front;
	while (og_str[*front] && og_str[*front] != ft_strchr("<>&", og_str[*front]))
	{
		if (pipe->input_string[*front] == D_QUOTES)
			*front += quotes_check(pipe->input_string + (*front), D_QUOTES);
		else if (pipe->input_string[*front] == S_QUOTES)
			*front += quotes_check(pipe->input_string + (*front), S_QUOTES);
		front++;
	}
	check_specialz(og_str, data, front);
}

void	check_specialz(char *str, t_data *data, int *front)
{
	if (str[*front] == '<')
	{
		if (str[*front + 1] == '<')
			data->special_char = D_LEFT_ARROW;
		else
			data->special_char = S_LEFT_ARROW;
	}
	else if (str[*front] == '>')
	{
		if (str[*front + 1] == '>')
			data->special_char = D_RIGHT_ARROW;
		else
			data->special_char = S_RIGHT_ARROW;
	}
	else if (str[*front] == '&' && str[*front + 1] == '&')
		data->special_char == AMPERZ;
	else
		data->special_char == NO_SPECIAL;
}
