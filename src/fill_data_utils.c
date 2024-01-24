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

static int	word_counter(char const *s, char c);
static int	string_size(char const *s, char c);

void	prepare_split(t_data *data, t_pipes *pipe, int *back, int *front)
{
	char	*og_str;

	og_str = pipe->input_string;
	*back = *front;
	while (og_str[*front] && !ft_strchr("<>&", og_str[*front]))
	{
		if (pipe->input_string[*front] == D_QUOTES)
			*front += quotes_check(pipe->input_string + (*front), D_QUOTES);
		else if (pipe->input_string[*front] == S_QUOTES)
			*front += quotes_check(pipe->input_string + (*front), S_QUOTES);
		else
			front++;
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

char	**special_splitens(char *str, int *front, char c)
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
	while (str[i] != '\0' && i < *front)
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		if (str[i] != '\0')
		{
			str_array[j] = ft_substr(str, i, string_size(str + i, c));
			j++;
		}
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	str_array[j] = 0;
	return (str_array);
}

static int	word_counter(char const *s, char c)
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

static int	string_size(char const *s, char c)
{
	int i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
	}
	return (i);
}