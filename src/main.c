/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:58:22 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/30 14:51:47 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	freezzzz(char *input);

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
			input = line_read();
			if (input && *input)
				add_history(input);
			freezzzz(input);
			// creat_list(&head, input);			
			// free(input);
			// input_str_tester(head);
			// organize_list(head);
			// tester(head);
			// execute_command(head, env);
			// coador(&head);
		}
		rl_clear_history();
	}
}

void	freezzzz(char *input)
{
	free(input);
}
