/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:36:46 by ruiolive          #+#    #+#             */
/*   Updated: 2024/02/01 09:54:49 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *line_read(void) /*#TODO add error messages*/
{
	char    *input;
	char	*new_line;
	int		check_empty;
	int		parenthesis;
	int		x;

	parenthesis = 0;
	check_empty = 0;
	x = 0;
	input = get_input();
	if (!parse_input(input, &parenthesis, &check_empty, &x))
			return (add_history(input), free(input), NULL);
	while (unfinished_command_line(input) || parenthesis != 0)
	{
		new_line = readline("> ");
		if (!(*new_line))
		{
			free(new_line);
			continue ;
		}
		input = ft_strjoin_v2(input, new_line);
		if (!parse_input(input, &parenthesis, &check_empty, &x) || parenthesis < 0) 
			return (add_history(input), free(input), NULL);
	}
	return (input);
}
