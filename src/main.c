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
	// t_pipes		*head;

	t_envs *head_envs;
	head_envs = create_env_list(env);
	// head = NULL;
	heardoc_read = NULL;
	(void)argv;
	(void)env;
	if (argc == 1)
	{
		while (1) 
		{
			count_struc.i = 0;
			count_struc.counter = 0;
			input = line_read(&heardoc_read, &count_struc);
			if (input && *input)
				add_history(input);
			else
				continue;
			// ft_cd(input);
			// ft_pwd();
			// ft_echo(input);
			// ft_export(head_envs,input);
			// ft_env(head_envs);
			ft_unset(&head_envs,input);
			// ft_env(head_envs);
			// creat_list(&head, input);			
			// input_str_tester(head);
			// freezzzz(input, &heardoc_read, &head);
			// organize_list(head);
			// tester(head);
			// execute_command(head, env);
			// coador(&head);
		}
		free_env_list(head_envs);
		rl_clear_history();
	}
}
