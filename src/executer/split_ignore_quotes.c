/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_ignore_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:16:44 by ruiolive          #+#    #+#             */
/*   Updated: 2024/03/29 14:18:24 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	word_counter(char *s, char *c);
static int	string_size(char *s, char *c);

char	**ft_split_ignore_quotes(char *s, char *c)
{
	char	**str_array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	str_array = malloc(sizeof(char *) * (word_counter(s, c) + 1));
	if (!str_array)
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] && ft_strchr(c, s[i]))
			i += all_quotes_ignore(s + i);
		if (s[i] != '\0')
		{
			str_array[j] = ft_substr(s, i, string_size(s + i, c));
			j++;
		}
		while (s[i] && !ft_strchr(c, s[i]))
			i += all_quotes_ignore(s + i);
	}
	str_array[j] = 0;
	return (str_array);
}

static int	word_counter(char *s, char *c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		while (s[i] && ft_strchr(c, s[i]))
			i += all_quotes_ignore(s + i);
		if (s[i] != '\0')
			counter++;
		while (s[i] && !ft_strchr(c, s[i]))
			i += all_quotes_ignore(s + i);
	}
	return (counter);
}

static int	string_size(char *s, char *c)
{
	int	i;

	i = 0;
	while (s[i] && !ft_strchr(c, s[i]))
		i += all_quotes_ignore(s + i);
	return (i);
}

int	all_quotes_ignore(char *s)
{
	if (*s == '\"')
		return (quote_ignore(s, D_QUOTES) + 1);
	else if (*s == '\'')
		return (quote_ignore(s, S_QUOTES) + 1);
	return (1);
}
