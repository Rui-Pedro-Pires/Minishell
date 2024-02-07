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

char	**ft_realloc(char ***heardoc_read, t_counter *count_struc);

void	check_for_heardoc(char ***heardoc_read, char *input, t_counter *count_struc)
{
	char	*new_line;

	while (input[count_struc->i])
	{
		if (input[count_struc->i] && input[count_struc->i] == '<')
			count_struc->i++;
		if (input[count_struc->i] && input[count_struc->i] == '<')
		{
			*heardoc_read = ft_realloc(heardoc_read, count_struc);
			while (1)
			{
				new_line = readline("> ");
				if (!new_line)
					return ;
				if (!(*new_line))
				{
					free(new_line);
					continue ;
				}
				else if (ft_strncmp(new_line, "eof", ft_strlen(new_line)) == 0)
				{
					free(new_line);
					(*heardoc_read)[count_struc->counter + 1] = 0;
					count_struc->i++;
					break ;
				}
				if (!(*(*heardoc_read)[count_struc->counter]))
				{
					free((*heardoc_read)[count_struc->counter]);
					(*heardoc_read)[count_struc->counter] = ft_strdup(new_line);
					free(new_line);
				}
				else
					(*heardoc_read)[count_struc->counter] = ft_strjoin_v3((*heardoc_read)[count_struc->counter], new_line);
			}
			count_struc->counter++;
		}
		count_struc->i++;
	}
}

char	**ft_realloc(char ***heardoc_read, t_counter *count_struc)
{
	char **copy;
	int	x;

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
