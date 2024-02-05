/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:36:46 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/31 12:24:17 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char *get_input(void);

char    *line_read(void) /*#TODO add error messages*/
{
	char    *input;
	char	*new_line;
	int		check_empty;
	int		parenthesis;

	parenthesis = 0;
	check_empty = 0;
	input = get_input();
	if (!parse_input(input) || !count_parenthesis(input, &parenthesis, &check_empty))
			return (add_history(input), free(input), NULL);
	while (unfinished_command_line(input) || read_command(input) || parenthesis != 0)
	{
		new_line = readline("> ");
		if (!(*new_line))
		{
			free(new_line);
			continue ;
		}
		if (!count_parenthesis(new_line, &parenthesis, &check_empty))
		{
			input = ft_strjoin_v2(input, new_line);
			return (add_history(input), free(input), NULL);
		}
		input = ft_strjoin_v2(input, new_line);
		if (!parse_input(input) || parenthesis < 0) 
			return (add_history(input), free(input), NULL);
	}
	return (input);
}

static char *get_input(void)
{
	char	*cwd;
	char    *input;

	cwd = creat_cwd();
	input = readline(cwd);
	free(cwd);
	return (input);
}

int	parse_input(char *input)
{
	int	i;

	i = 0;
	if (!quotes_parser(input))
		return (0);
	if (!check_begin_case(input, &i))
		return (0);
	if (!signs_parser(input, i))
		return (0);
	return (1);
}