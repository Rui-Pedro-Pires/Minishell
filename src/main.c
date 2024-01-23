/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:58:22 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/23 10:43:29 by ruiolive         ###   ########.fr       */
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
			check_unfinished_quotes(input);
			wrong_specialch_syntax(input);
			creat_list(&head, input);
			// organize_list(head);
			while (head)
			{
				printf("CMD: %s\n", head->input_string);
				printf("PIPE_TYPE: %d\n", head->pipe_type);
				head = head->next;
			}
			// execute_command(head, env);
			free(input);
		}
		rl_clear_history();
	}
}
