/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:45:24 by jorteixe          #+#    #+#             */
/*   Updated: 2024/02/08 11:45:53 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_chars(const char *str, const char *accept)
{
	const char	*a;

	while (*str)
	{
		a = accept;
		while (*a)
		{
			if (*a++ == *str)
			{
				return ((char *)str);
			}
		}
		str++;
	}
	return (NULL);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*new;

	len = ft_strnlen(s, n);
	new = malloc(len + 1);
	if (new == NULL)
		return (NULL);
	new[len] = '\0';
	return (ft_memcpy(new, s, len));
}

size_t	ft_strnlen(const char *str, size_t maxlen)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && i < maxlen)
		i++;
	return (i);
}

int	count_alphanum(char *str, int j)
{
	int	i;

	i = j;
	if (str[i] == '$' || (str[j] == '~' && j == 0))
	{
		i++;
	}
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		i++;
	}
	return (i);
}

char	*copy_inside_quotes(char *str)
{
	int		i;
	int		j;
	char	*clean_str;
	bool	single_open;
	bool	double_open;

	single_open = false;
	double_open = false;
	i = 0;
	j = 0;
	clean_str = malloc(ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == '\'' && !double_open)
			single_open = !single_open;
		else if (str[i] == '\"' && !single_open)
			double_open = !double_open;
		else
			clean_str[j++] = str[i];
		i++;
	}
	clean_str[j] = '\0';
	free(str);
	return (clean_str);
}
