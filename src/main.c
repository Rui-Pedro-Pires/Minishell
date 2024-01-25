/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:58:22 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/25 12:00:49 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_pipes	*head;

	head = NULL;
	(void)argv;
	(void)env;
	if (argc == 1)
	{
		while (1)
		{
			input = readline("");
			if (input && *input)
				add_history(input);
			else
				continue ;
			if (!check_unfinished_quotes(input)
				|| !wrong_specialch_syntax(input))
				continue ;
			creat_list(&head, input);
			free(input);
			// input_str_tester(head);
			organize_list(head);
			// tester(head);
			// execute_command(head, env);
			// coador(&head);
		}
		rl_clear_history();
	}
}
