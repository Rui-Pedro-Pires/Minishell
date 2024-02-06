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

void	check_for_heardoc(char **heardoc_read, char *input, t_counter *count_struc)
{
	char	*new_line;

	new_line = ft_strdup("");
	ft_realloc(heardoc_read); /*#TODO realloc function to do a copy of the heardoc, and creat with one more space*/
	heardoc_read = malloc(sizeof(char *) * (count_struc->counter + 2));
	heardoc_read[count_struc->counter] = ft_strdup("");
	while (input[count_struc->i])
	{
		if (input[count_struc->i] && input[count_struc->i] == '<' \
		&& input[count_struc->i + 1] == '<')
		{
			while (ft_strncmp(new_line, "eof", ft_strlen("eof")) != 0)
			{
				new_line = readline("> ");
				if (!(*new_line))
				{
					free(new_line);
					continue ;
				}
				heardoc_read[count_struc->counter] = ft_strjoin_v2(heardoc_read[count_struc->counter], new_line);
				printf("%s\n", heardoc_read[count_struc->counter]);
			}
			count_struc->counter++;
		}
		count_struc->i++;
	}
}
