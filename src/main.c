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
	t_counter	count_struc;
	t_pipes		*head;
	t_envs		*head_envs;
	t_init		init;

	head = NULL;
	init.heardoc_read = NULL;
	init.envs = create_env_list(env);
	// init.sorted_envs = function_sorted;
	(void)argv;
	(void)env;
	if (argc == 1)
	{
		while (1)
		{
			count_struc.i = 0;
			count_struc.counter = 0;
			input = line_read(&init.heardoc_read, &count_struc);
			if (input && *input)
				add_history(input);
			else
				continue ;
			input = check_quotes_n_expand(init.envs, input);
			creat_list(&head, input, init);
			free_input(&input);
			organize_list(head);
			tester(head);
			executer(head);
			// coador(&head);
			free_heardoc(&head->heardocs);
			free_list(&head);
		}
		free_env_list(head_envs);
		rl_clear_history();
	}
}
