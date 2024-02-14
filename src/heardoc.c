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

static char	*search_heardoc_condition(char *input, t_counter *iter);
static char	**ft_realloc(char ***heardoc_read, t_counter *iter);
static int	add_to_line(char **new_line, char *str, \
			char ***h_doc, t_counter *iter);

void	heardoc_check(char ***heardoc_read, char *input, t_counter *iter, int i)
{
	char	*new_line;
	char	*str_condition;

	while (input[iter->i] && iter->i < i)
	{
		if (input[iter->i] == D_QUOTES)
			iter->i += quote_ignore(input + iter->i, D_QUOTES);
		else if (input[iter->i] == S_QUOTES)
			iter->i += quote_ignore(input + iter->i, S_QUOTES);
		if (input[iter->i] && input[iter->i] == '<' && input[iter->i - 1] == '<')
		{
			str_condition = search_heardoc_condition(input, iter);
			if (!str_condition)
				return ;
			*heardoc_read = ft_realloc(heardoc_read, iter);
			while (1)
			{
				new_line = readline("> ");
				if (!add_to_line(&new_line, str_condition, \
				heardoc_read, iter))
				{
					free(str_condition);
					break ;
				}
			}
			iter->counter++;
		}
		iter->i++;
	}
}

static char	**ft_realloc(char ***heardoc_read, t_counter *iter)
{
	char	**copy;
	int		x;

	x = 0;
	copy = malloc(sizeof(char *) * (iter->counter + 2));
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

static int	add_to_line(char **new_line, char *str, char ***h_doc, t_counter *iter)
{
	if (!(*new_line))
		return (err_hlr_2(ERR_READ, str, NULL), 0);
	if (!(*(*new_line)))
	{
		free(*new_line);
		return (1);
	}
	if (ft_strncmp(*new_line, str, ft_strlen(*new_line)) == 0)
	{
		free(*new_line);
		(*h_doc)[iter->counter] = add_nl((*h_doc)[iter->counter], "\n");
		(*h_doc)[iter->counter + 1] = 0;
		iter->i++;
		return (0);
	}
	if (!(*(*h_doc)[iter->counter]))
	{
		free((*h_doc)[iter->counter]);
		(*h_doc)[iter->counter] = ft_strdup(*new_line);
		free(*new_line);
	}
	else
		(*h_doc)[iter->counter] = \
		str_join_with_newline((*h_doc)[iter->counter], *new_line);
	return (1);
}

static char	*search_heardoc_condition(char *input, t_counter *iter)
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
