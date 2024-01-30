/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:36:46 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/30 14:45:44 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *line_read(void)
{
	char    *input;
	char	*new_line;
	char	*cwd;
	int		parenthesis;

	parenthesis = 0;
	cwd = creat_cwd();
	input = readline(cwd);
	free(cwd);
	count_parenthesis(input, &parenthesis);
	while (unfinished_str(input) || parenthesis != 0)
	{
		if (!parse_input(input))
			return (add_history(input), free(input), NULL);
		new_line = readline("> ");
		if (!(*new_line))
		{
			free(new_line);
			continue ;
		}
		count_parenthesis(new_line, &parenthesis);
		input = ft_strjoin_v2(input, new_line);
	}
	return (input);
}
