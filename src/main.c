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

int					g_return_value;

int	main(void)
{
	char		*input;
	t_pipes		*head;
	t_init		init;
	int			heardoc_index;

	head = NULL;
	initialize(&init);
	while (1)
	{
		iterative_mode();
		heardoc_index = -1;
		init.pid = NULL;
		init.heardocs = NULL;
		init.heardoc_index = &heardoc_index;
		input = line_read(&init);
		process_input(&head, input, &init);
		free_input(&input);
		free_heardoc(head);
		free_list(&head);
	}
	free_env_list(init.envs);
	rl_clear_history();
}

void	initialize(t_init *init)
{
	char	**env;

	env = __environ;
	init->envs = create_env_list(env, true);
	init->sorted_envs = create_env_list(env, false);
	init->sorted_envs = bubble_sort(init->sorted_envs);
}

void	process_input(t_pipes **head, char *input, t_init *init)
{
	if (input && *input)
		add_history(input);
	else
	{
		free_args(init->heardocs);
		return ;
	}
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
