/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:30:38 by jorteixe          #+#    #+#             */
/*   Updated: 2024/03/26 15:40:33 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_questionmark(t_pipes *piper, char *str, int j);
char	*expand_questionmark(t_pipes *piper, char *before, char *after);
char	*check_quotes_n_expand(t_pipes *piper, char *str)
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
		if (str[0] == '~' && !single_open)
			str = handle_til(piper, str, j);
		if (str[j] == '$' && !single_open && str[j + 1] == '?')
			str = handle_questionmark(piper, str, j);
		if (str[j] == '$' && !single_open && (ft_isalnum(str[j + 1]) || str[j
				+ 1] == '_'))
			str = handle_dollar_sign(piper, str, j, single_open);
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

char	*handle_dollar_sign(t_pipes *piper, char *str, int j, bool single_open)
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
		str = expand(piper, bef_str, var_name, aft_str);
	}
	return (str);
}

char	*handle_til(t_pipes *piper, char *str, int j)
{
	char	*bef_str;
	char	*aft_str;
	char	*var_name;
	size_t	i;

	bef_str = ft_strdup("");
	i = count_alphanum(str, j);
	if (i < ft_strlen(str))
		aft_str = ft_strdup(str + i);
	else
		aft_str = ft_strdup("");
	var_name = ft_strdup("HOME");
	free(str);
	str = expand(piper, bef_str, var_name, aft_str);
	return (str);
}

char	*expand(t_pipes *piper, char *before, char *str, char *after)
{
	char	*var_value;
	char	*new_str;
	int		full_string_count;
	t_envs	*head;

	head = piper->init.envs;
	var_value = ft_getenv(head, str);
	if (var_value == NULL)
		var_value = ft_strdup("");
	full_string_count = ft_strlen(before) + ft_strlen(var_value)
		+ ft_strlen(after) + 2;
	new_str = ft_calloc(full_string_count, sizeof(char));
	ft_strlcpy(new_str, before, full_string_count);
	if (*var_value)
		ft_strlcat(new_str, var_value, full_string_count);
	if (*after)
		ft_strlcat(new_str, after, full_string_count);
	free(before);
	before = NULL;
	free(after);
	after = NULL;
	free(str);
	str = NULL;
	free(var_value);
	return (new_str);
}

char	*handle_questionmark(t_pipes *piper, char *str, int j)
{
	char	*bef_str;
	char	*aft_str;
	size_t	i;

	bef_str = ft_strndup(str, j);
	i = j + 2;
	if (i < ft_strlen(str))
		aft_str = ft_strdup(str + i);
	else
		aft_str = ft_strdup("");
	free(str);
	str = expand_questionmark(piper, bef_str, aft_str);
	return (str);
}

char	*expand_questionmark(t_pipes *piper, char *before, char *after)
{
	char *new_str;
	int full_string_count;
	char *var_value;

	var_value = ft_itoa(piper->init.return_value);
	full_string_count = ft_strlen(before) + ft_strlen(var_value)
		+ ft_strlen(after) + 2;
	new_str = ft_calloc(full_string_count, sizeof(char));
	ft_strlcpy(new_str, before, full_string_count);
	if (*var_value)
		ft_strlcat(new_str, var_value, full_string_count);
	if (*after)
		ft_strlcat(new_str, after, full_string_count);
	free(before);
	before = NULL;
	free(after);
	after = NULL;
	free(var_value);
	return (new_str);
}