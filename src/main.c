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
	t_init		init;

	head = NULL;
	init.envs = create_env_list(env);
	init.sorted_envs = create_env_list(env);
	init.sorted_envs = bubble_sort(init.sorted_envs);
	(void) argv;
	(void) argc;
	while (1)
	{
		count_struc.i = 0;
		count_struc.counter = 0;
		init.heardocs = NULL;
		init.heardoc_index = -1;
		input = line_read(&init.heardocs, &count_struc, init);
		if (input && *input)
			add_history(input);
		else
			continue ;
		if (check_for_dbpipe_dbamper(input))
		{
			creat_list(&head, input, init, 1);
			head->init.return_value = recursive_executer(head, 0);
		}
		else
		{
			creat_list(&head, input, init, 0);
			head->init.return_value = list_iterator_executer(head);
		}
		printf("%d\n", head->init.return_value);
		free_input(&input);
		free_heardoc(head);
		free_list(&head);
	}
	free_env_list(init.envs);
	rl_clear_history();
}
