/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heardoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive  <ruiolive@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:22:04 by ruiolive          #+#    #+#             */
/*   Updated: 2024/02/28 10:22:04 by ruiolive         ###   ########.fr       */
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
	while (input[i] && !ft_strchr("|&>< ", input[i]))
		i++;
	str_condition = malloc(sizeof(char) * (i - iter->i + 1));
	if (!str_condition)
		return (NULL);
	while (input[j] && !ft_strchr("|&>< ", input[j]))
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
