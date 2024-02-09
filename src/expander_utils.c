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

char *	check_quotes_for_expand(char *str)
{
	int		j;
	bool	single_open;
	bool	double_open;
	char  *bef_str;
	char *aft_str;

	j = 0;
	single_open = false;
	double_open = false;
	while (str[j])
	{
		if (str[j] == '\'' && !double_open && !single_open)
			single_open = true;
		else if (str[j] == '\'' && !double_open && single_open)
			single_open = false;
		if (str[j] == '\"' && !single_open && !double_open)
			double_open = true;
		else if (str[j] == '\"' && !single_open && double_open)
			double_open = false;
		if (str[j] == '$' && !single_open)
		{
			ft_strlcpy(bef_str, str, j)
			#TODO before function
			#TODO after function
			str = expand(str, BEFORE, AFTER);
		}
		j++;
	}
}

void update_quote_status(char c, bool *single_open, bool *double_open) {
    if (c == '\'' && !*double_open) *single_open = !*single_open;
    if (c == '\"' && !*single_open) *double_open = !*double_open;
}

void handle_dollar_sign(char *str, int j, bool single_open) {
    if (str[j] == '$' && !single_open) {
        char *bef_str = strndup(str, j);
        char *aft_str = ft_strdup(str + j + 1);
        str = expand(str, bef_str, aft_str);
        free(bef_str);
        free(aft_str);
    }
}

char	*expand(char *str, char *BEFORE, char *AFTER)
{
	char	*start;
	char	*end;

	char	*var_name;
	char	*var_value;
	char	*new_str;

	start = strchr(str, '$');
	if (start == NULL)
		return (strdup(str));
	end = check_chars(start, "/ \"");
	if (end == NULL)
		end = start + strlen(start);
	var_name = strndup(start + 1, end - start - 1);
	var_value = getenv(var_name);
	if (var_value == NULL)
		var_value = "";
	new_str = malloc(strlen(str) - ft_strlen(var_name) + ft_strlen(var_value)
			+ 1);
	ft_strncpy(new_str, str, start - str);
	new_str[start - str] = '\0';
	ft_strcat(new_str, var_value);
	ft_strcat(new_str, end);
	free(var_name);
	#TODO join new str + before + after
	return (new_str);
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

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	for (; i < n; i++)
	{
		dest[i] = '\0';
	}
	return (dest);
}

char	*ft_strcat(char *dest, const char *src)
{
	char *rdest = dest;

	while (*dest)
		dest++;
	while ((*dest++ = *src++))
		;
	return (rdest);
}