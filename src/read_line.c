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

static char	*get_input(void);

char	*line_read(char ***heardoc_read, t_counter *counter_struc)
{
	char	*input;

	counter_struc->prnt = 0;
	input = get_input();
	count_parenthesis(input, counter_struc);
	if (!parse_input(input, counter_struc, heardoc_read))
		return (add_history(input), free(input), NULL);
	input = keep_reading(input, counter_struc, heardoc_read);
	return (input);
}

char	*keep_reading(char *input_rec, t_counter *c_struc, char ***heardoc_read)
{
	char	*new_line;
	char	*input;

	input = input_rec;
	while (unfinished_command_line(input) || c_struc->prnt != 0)
	{
		new_line = readline("> ");
		if (!new_line)
			return (NULL);
		if (!(*new_line))
		{
			free(new_line);
			continue ;
		}
		count_parenthesis(new_line, c_struc);
		input = str_join_with_space(input, new_line);
		if (!parse_input(input, c_struc, heardoc_read) \
		|| c_struc->prnt < 0)
			return (add_history(input), free(input), NULL);
	}
	return (input);
}

static char	*get_input(void)
{
	char	*cwd;
	char	*input;

	cwd = creat_cwd();
	input = readline(cwd);
	if (!input)
	{
		free(cwd);
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	free(cwd);
	return (input);
}
