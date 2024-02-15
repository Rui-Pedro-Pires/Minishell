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

#include "../includes/minishell.h"

char	*check_quotes_n_expand(char *str)
{
	int		j;
	bool	single_open;
	bool	double_open;

	j = 0;
	single_open = false;
	double_open = false;
	while (str[j])
	{
		update_quote_status(str[j], &single_open, &double_open);
		if (str[j] == '$' && !single_open && (ft_isalnum(str[j + 1]) || str[j
				+ 1] == '_'))
			str = handle_dollar_sign(str, j, single_open); /* #TODO  Handle*/
		j++;
	}
	str = copy_inside_quotes(str);
	return (str);
}

void	update_quote_status(char c, bool *single_open, bool *double_open)
{
	if (c == '\'' && !*double_open)
		*single_open = !*single_open;
	if (c == '\"' && !*single_open)
		*double_open = !*double_open;
}

char	*handle_dollar_sign(char *str, int j, bool single_open)
{
	char	*bef_str;
	char	*aft_str;
	char	*var_name;
	size_t	i;

	if (str[j] == '$' && !single_open)
	{
		bef_str = ft_strndup(str, j);
		i = count_alphanum(str, j);
		if (i < ft_strlen(str))
			aft_str = ft_strdup(str + i);
		else
			aft_str = ft_strdup("");
		var_name = ft_strndup(str + j + 1, i - (j + 1));
		free(str);
		str = expand(bef_str, var_name, aft_str);
	}
	return (str);
}

char	*expand(char *before, char *str, char *after)
{
    char	*var_value;
    char	*new_str;
    int		full_string_count;

    var_value = getenv(str);
    if (var_value == NULL)
        var_value = "/";
    full_string_count = ft_strlen(before) + ft_strlen(var_value)
        + ft_strlen(after) + 1;
    new_str = malloc(full_string_count);
    ft_strlcpy(new_str, before, full_string_count);
    if (*var_value)
        ft_strlcat(new_str, var_value, full_string_count);
    if (*after)
        ft_strlcat(new_str, after, full_string_count);
    free(before);
    free(after);
    free(str);
    return (new_str);
}

char	*copy_alphanumeric(const char *src)
{
	char	*dest;
	int		j;
	int		i;

	dest = malloc(strlen(src) + 1);
	j = 0;
	i = 0;
	while (src[i])
	{
		if (ft_isalnum(src[i]) || src[i] == '_')
		{
			dest[j] = src[i];
			j++;
		}
		i++;
	}
	dest[j] = '\0'; // Null-terminate the destination string
	return (dest);
}

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
	if (str[i] == '$')
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
	clean_str = malloc(strlen(str) + 1);
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
	return (clean_str);
}
