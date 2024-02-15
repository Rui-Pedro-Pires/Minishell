/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testerzzzz.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:39:03 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/25 11:15:19 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	tester(t_pipes *head)
{
	int		i;
	int		j;
	int		x;

	x = 0;
	while (head)
	{
		i = 0;
		printf(" ________________________________________________________\n");
		printf("|                                                        |\n");
		printf("|                        "GRN"NODE %d\n"RESET, x);
		printf("|--------------------------------------------------------|\n");
		printf("| "BLU"Input String:"RESET" %s\n",head->input_string);
		printf("|--------------------------------------------------------|\n");
		if (head->empty_node == true)
		{
			head = head->next;
			printf("|________________________________________________________|\n");
			continue ;
		}
		while (head->data[i].command_n_args)
		{
			j = 1;
			printf("| "RED"COMMAND:"RESET" %s\n", head->data[i].command_n_args[0]);
			printf("|--------------------------------------------------------|\n");
			printf("| "CYN"COMMAND TYPE[%d]:"RESET" %u\n", x,
					head->data[i].command_type);
			printf("|--------------------------------------------------------|\n");
			printf("| "MAG"ARGS: "RESET);
			while (head->data[i].command_n_args[j])
			{
				printf("%s", head->data[i].command_n_args[j]);
				j++;
			}
			printf("\n");
			printf("|--------------------------------------------------------|\n");
			printf("|________________________________________________________|\n");
			i++;
		}
		head = head->next;
		x++;
	}
}

void    input_str_tester(t_pipes *head)
{
    if (!head)
        return ;
    while (head)
    {
        printf("%s\n", head->input_string);
        head = head->next;  
    }
}
