/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heardoc_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive  <ruiolive@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:55:58 by ruiolive          #+#    #+#             */
/*   Updated: 2024/02/06 15:55:58 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	heardoc_check(char ***heardoc_read, char *input, t_counter *count_struc)
{
	char	*new_line;
	char	*str_condition;

	while (input[count_struc->i])
	{
		if (input[count_struc->i] && input[count_struc->i] == '<')
			count_struc->i++;
		if (input[count_struc->i] && input[count_struc->i] == '<')
		{
			str_condition = search_heardoc_condition(input, count_struc);
			*heardoc_read = ft_realloc(heardoc_read, count_struc);
			while (1)
			{
				new_line = readline("> ");
				if (!add_to_line(&new_line, str_condition, \
				heardoc_read, count_struc))
				{
					free(str_condition);
					break ;
				}
			}
			count_struc->counter++;
		}
		count_struc->i++;
	}
}

char	**ft_realloc(char ***heardoc_read, t_counter *count_struc)
{
	char	**copy;
	int		x;

	x = 0;
	copy = malloc(sizeof(char *) * (count_struc->counter + 2));
	if (!copy)
		return (NULL);
	if (!(*heardoc_read))
	{
		copy[0] = ft_strdup("");
		copy[1] = 0;
		return (copy);
	}
	while ((*heardoc_read)[x])
	{
		copy[x] = ft_strdup((*heardoc_read)[x]);
		free((*heardoc_read)[x]);
		x++;
	}
	copy[x] = ft_strdup("");
	x++;
	copy[x] = 0;
	free((*heardoc_read));
	return (copy);
}

int	add_to_line(char **new_line, char *str, char ***h_doc, t_counter *counter)
{
	if (!(*new_line))
		return (0);
	if (!(*(*new_line)))
	{
		free(*new_line);
		return (1);
	}
	if (ft_strncmp(*new_line, str, ft_strlen(*new_line)) == 0)
	{
		free(*new_line);
		(*h_doc)[counter->counter] = add_nl((*h_doc)[counter->counter], "\n");
		(*h_doc)[counter->counter + 1] = 0;
		counter->i++;
		return (0);
	}
	if (!(*(*h_doc)[counter->counter]))
	{
		free((*h_doc)[counter->counter]);
		(*h_doc)[counter->counter] = ft_strdup(*new_line);
		free(*new_line);
	}
	else
		(*h_doc)[counter->counter] = \
		str_join_with_newline((*h_doc)[counter->counter], *new_line);
	return (1);
}

char	*search_heardoc_condition(char *input, t_counter *count_struc)
{
	int		i;
	int		x;
	int		j;
	char	*str_condition;

	x = 0;
	count_struc->i += 1;
	while (input[count_struc->i] && input[count_struc->i] == ' ')
		count_struc->i++;
	i = count_struc->i;
	j = count_struc->i;
	while (input[i] && (!ft_strchr("|&><", input[i]) || input[i] != ' '))
		i++;
	str_condition = malloc(sizeof(char) * i + 1);
	if (!str_condition)
		return (NULL);
	while (input[j] && (!ft_strchr("|&><", input[j]) \
	|| input[j] != ' '))
		str_condition[x++] = input[j++];
	str_condition[x] = '\0';
	return (str_condition);
}
