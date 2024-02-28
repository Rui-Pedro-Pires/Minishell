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

void	prepare_split(t_pipes *head, int *size)
{
	char	*og_str;

	og_str = head->input_string;
	while (og_str[(*size)] && !ft_strchr("<>", og_str[(*size)]))
	{
		if (og_str[(*size)] == D_QUOTES)
			*size += quote_ignore(og_str + (*size), D_QUOTES);
		else if (og_str[(*size)] == S_QUOTES)
			*size += quote_ignore(og_str + (*size), S_QUOTES);
		else if (og_str[(*size)] == '(')
			*size = parenthesis_ignore(og_str + (*size)) + 1;
		else
			(*size)++;
	}
}

char	**special_splitens(char *str, int size, char c)
{
	char	**str_array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	str_array = malloc(sizeof(char *) * (counte_words(str, c, size) + 1));
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
	str_array[j] = 0;
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

int	fill_data(t_pipes *head)
{
	int		size;

	size = 0;
	prepare_split(head, &size);
	head->data.command_n_args = special_splitens(head->input_string, size, 32);
	if (!command_decider1(head) && !command_decider2(head))
		head->data.command_type = NOT_BUILTIN;
	return (0);
}
