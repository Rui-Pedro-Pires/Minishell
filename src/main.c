/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:58:22 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/24 15:40:35 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_pipes	*head;
	int i;
	int j;
	int x = 0;

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
			if (!check_unfinished_quotes(input) \
			|| !wrong_specialch_syntax(input))
				continue ;
			creat_list(&head, input);
			organize_list(head);
			x = 0;
			while (head)
			{
				i = 0;
				printf("Input String: %s", head->input_string);
				while (head->data[i].command_n_args)
				{
					j = 0;
					while (head->data[i].command_n_args[j])
					{
						printf("CMD[%d][%d]: %s\n",x, j , head->data[i].command_n_args[j]);
						printf("CMN TYPE[%d]: %d\n",x , head->data[i].command_type);
						j++;
					}
					i++;
				}
				// printf("PIPE_TYPE: %d\n", head->pipe_type);
				head = head->next;
				x++;
			}
			// execute_command(head, env);
			free(input);
		}
		rl_clear_history();
	}
}
