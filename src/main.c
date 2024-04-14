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

int		g_return_value;
void	initialize(t_init *init, char **env);
void	process_input(t_pipes **head, char *input, t_init *init);

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_counter	count_struc;
	t_pipes		*head;
	t_init		init;
	int	heardoc_index;

	head = NULL;
	initialize(&init, env);
	(void)argv;
	(void)argc;
	while (1)
	{
		handle_iterative_mode();
		count_struc.i = 0;
		count_struc.counter = 0;
		heardoc_index = -1;
		init.pid = NULL;
		init.heardocs = NULL;
		init.heardoc_index = &heardoc_index;
		input = line_read(&init, &count_struc);		
		process_input(&head, input, &init);
		free_input(&input);
		free_heardoc(head);
		free_list(&head);
	}
	free_env_list(init.envs);
	rl_clear_history();
}

void	initialize(t_init *init, char **env)
{
	init->envs = create_env_list(env);
	init->sorted_envs = create_env_list(env);
	init->sorted_envs = bubble_sort(init->sorted_envs);
}

void	process_input(t_pipes **head, char *input, t_init *init)
{
	if (input && *input)
		add_history(input);
	else
		return;
	if (check_for_dbpipe_dbamper(input))
	{
		creat_list(head, input, init, 1);
		g_return_value = recursive_executer(*head, 0, *head);
	}
	else
	{
		creat_list(head, input, init, 0);
		g_return_value = list_iterator_executer(*head, *head);
	}
}
