/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitspec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:16:44 by ruiolive          #+#    #+#             */
/*   Updated: 2024/03/25 11:32:12 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	word_counter(char *s, char c);
static int	string_size(char *s, char c);
static int  all_quotes_ignore(char *s);

char	**ft_splitspec(char *s, char c)
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
		while (s[i] == c && s[i] != '\0')
			i += all_quotes_ignore(s + i);
		if (s[i] != '\0')
		{
			str_array[j] = ft_substr(s, i, string_size(s + i, c));
			j++;
		}
		while (s[i] != c && s[i] != '\0')
			i += all_quotes_ignore(s + i);
	}
	str_array[j] = 0;
	return (str_array);
}

static int	word_counter(char *s, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
		{
			i += all_quotes_ignore(s + i);
		    i++;
		}
		if (s[i] != '\0')
		{
			counter++;
		}
		while (s[i] != c && s[i] != '\0')
		{
			i += all_quotes_ignore(s + i);
		    i++;
		}
	}
	return (counter);
}

static int	string_size(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i += all_quotes_ignore(s + i);
		i++;
	}
	return (i);
}

static int  all_quotes_ignore(char *s)
{
    if (*s == '\"')
        return (quote_ignore(s, '\"'));
	else if (*s == '\'')
	    return (quote_ignore(s, '\''));
    return (1);
}
