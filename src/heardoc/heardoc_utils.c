/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heardoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:22:04 by ruiolive          #+#    #+#             */
/*   Updated: 2024/03/31 11:24:28 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*search_heardoc_condition(char *input, t_counter *iter)
{
	int		i;
	int		x;
	int		j;
	char	*str_condition;

	x = 0;
	iter->i += 2;
	while (input[iter->i] && input[iter->i] == ' ')
		iter->i++;
	i = iter->i;
	j = iter->i;
	if (ft_strchr("|<>()\\;", input[iter->i]))
		return (NULL);
	while (input[i] && !ft_strchr("|&>< ()", input[i]))
		i += all_quotes_ignore(input + i);
	str_condition = malloc(sizeof(char) * (i - iter->i + 1));
	if (!str_condition)
		return (NULL);
	while (j < i)
		str_condition[x++] = input[j++];
	str_condition[x] = '\0';
	return (str_condition);
}

int	maxlen(size_t new, size_t str_cond)
{
	if (new > str_cond)
		return (new);
	return (str_cond);
}

int	quotes_ignore(char *input)
{
	int	i;

	i = 0;
	if (input[i] == D_QUOTES)
		i += quote_ignore(input + i, D_QUOTES);
	else if (input[i] == S_QUOTES)
		i += quote_ignore(input + i, S_QUOTES);
	return (i);
}

char	*expande_heardoc(t_init init, char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == '$' && str[j + 1] == '?')
			str = handle_questionmark(init, str, j);
		if (str[j] == '$' && (ft_isalnum(str[j + 1]) || str[j + 1] == '_'))
			str = handle_dollar_sign_heardoc(init, str, j);
		j++;
	}
	return (str);
}

char	*handle_dollar_sign_heardoc(t_init init, char *str, int j)
{
	char	*bef_str;
	char	*aft_str;
	char	*var_name;
	size_t	i;

	if (str[j] == '$')
	{
		bef_str = ft_strndup(str, j);
		i = count_alphanum(str, j);
		if (i < ft_strlen(str))
			aft_str = ft_strdup(str + i);
		else
			aft_str = ft_strdup("");
		var_name = ft_strndup(str + j + 1, i - (j + 1));
		free(str);
		str = expand(init, bef_str, var_name, aft_str);
	}
	return (str);
}
