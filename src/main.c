/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:58:22 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/31 15:14:18 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*input;
	char		**heardoc_read;
	t_counter	count_struc;
	t_pipes		*head;

	head = NULL;
	heardoc_read = NULL;
	(void)argv;
	(void)env;
	if (argc == 1)
	{
		while (1)
		{
			input = line_read(&heardoc_read, &count_struc);
			if (input && *input)
				add_history(input);
			else
				continue;
			creat_list(&head, input);			
			input_str_tester(head);
			freezzzz(input, &heardoc_read, &head);
			// organize_list(head);
			// tester(head);
			// execute_command(head, env);
			// coador(&head);
		}
		rl_clear_history();
	}
}
