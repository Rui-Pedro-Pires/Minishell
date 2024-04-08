/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:58:22 by ruiolive          #+#    #+#             */
/*   Updated: 2024/04/06 11:49:05 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	global_return_value;
int	signal_return;

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_counter	count_struc;
	t_pipes		*head;
	t_init		init;
	int			heardoc_index;

	head = NULL;
	init.envs = create_env_list(env);
	init.sorted_envs = create_env_list(env);
	init.sorted_envs = bubble_sort(init.sorted_envs);
	(void) argv;
	(void) argc;
	handle_iterative_mode();
	while (1)
	{
		count_struc.i = 0;
		count_struc.counter = 0;
		init.heardocs = NULL;
		heardoc_index = -1;
		init.heardoc_index = &heardoc_index;
		input = line_read(&init, &count_struc);
		if (input && *input)
			add_history(input);
		else
			continue ;
		if (check_for_dbpipe_dbamper(input))
		{
			creat_list(&head, input, &init, 1);
			global_return_value = recursive_executer(head, 0);
		}
		else
		{
			creat_list(&head, input, &init, 0);
			global_return_value = list_iterator_executer(head);
		}
		free_input(&input);
		free_heardoc(head);
		free_list(&head);
	}
	free_env_list(init.envs);
	rl_clear_history();
}
