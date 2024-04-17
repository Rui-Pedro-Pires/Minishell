/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:53:52 by jorteixe          #+#    #+#             */
/*   Updated: 2024/04/11 10:54:15 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_questionmark(t_init init, char *str, int j)
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
	str = expand_questionmark(init, bef_str, aft_str);
	return (str);
}

char	*expand_questionmark(t_init init, char *before, char *after)
{
	char	*new_str;
	int		full_string_count;
	char	*var_value;

	(void)init;
	var_value = ft_itoa(g_return_value);
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

char	*expand_tilde(t_init init, char *before, char *after)
{
	char	*new_str;
	int		full_string_count;
	char	*var_value;

	var_value = ft_getenv(init.envs, "HOME");
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
	free(var_value);
	return (new_str);
}
