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

#include "../../../includes/minishell.h"

static int	counte_words(char const *s, char c, int size);
static int	string_size(char const *s, char c, int size);

void	prepare_split(t_data *data, t_pipes *head, int *back, int *front)
{
	char	*og_str;

	(void)data;
	og_str = head->input_string;
	*back = *front;
	while (og_str[(*front)] && !ft_strchr("<>", og_str[(*front)]))
	{
		if (og_str[(*front)] == D_QUOTES)
			*front += quote_ignore(og_str + (*front), D_QUOTES);
		else if (og_str[(*front)] == S_QUOTES)
			*front += quote_ignore(og_str + (*front), S_QUOTES);
		else if (og_str[(*front)] == '(')
			*front = parenthesis_ignore(og_str + (*front)) + 1;
		else
			(*front)++;
	}
}

void	check_specialz(char *str, t_data *data, int *front)
{
	if (!str[*front])
	{
		data->special_char = NO_SPECIAL;
		return ;
	}
	if (str[*front] == '<')
	{
		if (str[*front + 1] && str[*front + 1] == '<')
		{
			data->special_char = D_LEFT_ARROW;
			*front += 2;
		}
		else
		{
			data->special_char = S_LEFT_ARROW;
			*front += 1;
		}
	}
	else if (str[*front] == '>')
	{
		if (str[*front + 1] && str[*front + 1] == '>')
		{
			data->special_char = D_RIGHT_ARROW;
			*front += 2;
		}
		else
		{
			data->special_char = S_RIGHT_ARROW;
			*front += 1;
		}
	}
	else
		data->special_char = NO_SPECIAL;
}

char	**special_splitens(char *str, int *back, int *front, char c)
{
	char	**str_array;
	int		i;
	int		j;
	int		size;

	i = 0;
	j = 0;
	size = *front - *back;
	if (!str)
		return (NULL);
	str_array = ft_calloc(sizeof(char *), (counte_words(str, c, size) + 1));
	if (!str_array)
		return (NULL);
	while (str[i] && i < size)
	{
		while (str[i] && str[i] == c && i < size)
			i++;
		if (str[i])
			str_array[j++] = ft_substr(str, i, string_size(str + i, c, size));
		while (str[i] && str[i] != c && i < size)
			i++;
	}
	return (str_array);
}

static int	string_size(char const *s, char c, int size)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c && i < size)
		i++;
	return (i);
}
static int	counte_words(char const *s, char c, int size)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i] && i < size)
	{
		while (s[i] && s[i] == c && i < size)
			i++;
		if (s[i])
			counter++;
		while (s[i] && s[i] != c && i < size)
			i++;
	}
	return (counter);
}


int	fill_data(t_pipes *head, int count)
{
	int		i;
	int		back;
	int		front;
	t_data	*data;

	data = head->data;
	i = 0;
	front = 0;
	if (!data)
		return (0);
	while (i < count)
	{
		prepare_split(&data[i], head, &back, &front);
		data[i].command_n_args = special_splitens(head->input_string
				+ back, &back, &front, 32);
		check_specialz(head->input_string, &data[i], &front);
		if (!command_decider1(&data[i]) && !command_decider2(&data[i]))
			data[i].command_type = NOT_BUILTIN;
		i++;
	}
	data[i].command_n_args = NULL;
	return (0);
}
