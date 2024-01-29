/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/25 09:33:58 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			word_counter(char const *s, char c);
static int	string_size(char const *s, char c);

void	prepare_split(t_data *data, t_pipes *pipe, int *back, int *front)
{
	char	*og_str;

	og_str = pipe->input_string;
	*back = *front;
	while (og_str[(*front)] && !ft_strchr("<>&", og_str[(*front)]))
	{
		if (pipe->input_string[(*front)] == D_QUOTES)
			*front += quotes_check(pipe->input_string + (*front), D_QUOTES);
		else if (pipe->input_string[(*front)] == S_QUOTES)
			*front += quotes_check(pipe->input_string + (*front), S_QUOTES);
		else
			(*front)++;
	}
	check_specialz(og_str, data, front);
}

void	check_specialz(char *str, t_data *data, int *front)
{
	if (str[*front] == '<')
	{
		if (str[*front + 1] && str[*front + 1] == '<')
			data->special_char = D_LEFT_ARROW;
		else
			data->special_char = S_LEFT_ARROW;
	}
	else if (str[*front] == '>')
	{
		if (str[*front + 1] && str[*front + 1] == '>')
			data->special_char = D_RIGHT_ARROW;
		else
			data->special_char = S_RIGHT_ARROW;
	}
	else if (str[*front + 1] && str[*front] == '&' && str[*front + 1] == '&')
		data->special_char = AMPERZ;
	else
		data->special_char = NO_SPECIAL;
}

char	**special_splitens(char *str, int *back, int *front, char c)
{
	char	**str_array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	str_array = malloc(sizeof(char *) * (word_counter(str, c) + 1));
	if (!str_array)
		return (NULL);
	while (str[i] != '\0' && i < (*front - *back))
	{
		while (str[i] == c && str[i] != '\0' && i < (*front - *back))
			i++;
		if (str[i] != '\0')
		{
			str_array[j] = ft_substr(str, i, string_size(str + i, c));
			j++;
		}
		while (str[i] != c && str[i] != '\0' && i < (*front - *back))
			i++;
	}
	str_array[j] = 0;
	return (str_array);
}

static int	string_size(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	fill_data(t_pipes *pipe_struct, int count)
{
	int		i;
	int		back;
	int		front;
	t_data	*data;

	data = pipe_struct->data;
	i = 0;
	front = 0;
	while (i < count)
	{
		prepare_split(&data[i], pipe_struct, &back, &front);
		data[i].command_n_args = special_splitens(pipe_struct->input_string
				+ back, &back, &front, 32);
		if (!command_decider1(&data[i]) && !command_decider2(&data[i]))
			data[i].command_type = NOT_BUILTIN;
		i++;
	}
	return (0);
}
