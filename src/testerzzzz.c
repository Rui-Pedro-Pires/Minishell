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
	int		j;
	int		x;

	x = 0;
	while (head)
	{
		j = 0;
		printf(" ________________________________________________________\n");
		printf("|                                                        |\n");
		printf("|                        "GRN"NODE %d\n"RESET, x);
		printf("|--------------------------------------------------------|\n");
		printf("| "BLU"Input String:"RESET" %s\n",head->input_string);
		printf("|--------------------------------------------------------|\n");
		printf("| "RED"COMMAND:"RESET" %s\n", head->data.command_n_args[0]);
		printf("|--------------------------------------------------------|\n");
		printf("| "CYN"COMMAND TYPE[%d]:"RESET" %u\n", x, head->data.command_type);
		printf("|--------------------------------------------------------|\n");
		printf("| "MAG"ARGS: "RESET);
		while (head->data.command_n_args[j])
		{
			printf("(%s) ", head->data.command_n_args[j]);
			j++;
		}
		printf("\n");
		printf("|--------------------------------------------------------|\n");
		printf("|________________________________________________________|\n");
		head = head->next;
		x++;
	}
}

void    input_str_tester(t_pipes *head, int type)
{
    if (!head)
        return ;
	else
	{
		if (type == 1)
		{
			printf(""BLU"STR: %s\n"RESET"", head->input_string);
			printf(""BLU"Pipe_type: %d\n"RESET"", head->pipe_type);
		}
		else
		{
			printf(""RED"STR: %s\n"RESET"", head->input_string);
			printf(""RED"Pipe_type: %d\n"RESET"", head->pipe_type);
		}
		input_str_tester(head->down, 2);
		input_str_tester(head->next, 1);
	}
}

void	ft_print_heardoc(char **heardoc_read)
{
	int	i;

	i = 0;
	if (!heardoc_read)
		return ;
	while (heardoc_read[i])
	{
		printf("--------------------------------\n");
		printf("%s", heardoc_read[i]);
		i++;
	}
}