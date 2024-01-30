/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:36:46 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/30 16:17:32 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char *get_input(void);
static int	parse_input(char *input);

char    *line_read(void)
{
	char    *input;
	char	*new_line;
	int		parenthesis;

	parenthesis = 0;
	input = get_input();
	count_parenthesis(input, &parenthesis);
	if (!parse_input(input))
			return (add_history(input), free(input), NULL);
	while (unfinished_command_line(input) || parenthesis != 0)
	{
		if (!parse_input(input) || parenthesis < 0) /*#TODO add message error, parenthesis error*/
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

static char *get_input(void)
{
	char	*cwd;
	char    *input;

	cwd = creat_cwd();
	input = readline(cwd);
	free(cwd);
	return (input);
}

static int	parse_input(char *input)
{
	if (!check_unfinished_quotes(input)
		|| !wrong_specialch_syntax(input))
		return (0);
	return (1);
}