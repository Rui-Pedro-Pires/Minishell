/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive  <ruiolive@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:15:59 by ruiolive          #+#    #+#             */
/*   Updated: 2024/02/26 13:15:59 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	add_to_list(t_pipes **head, char *formated, int status, \
t_init *init);

void	creat_list(t_pipes **head, char *input, t_init *init, int status)
{
	int			i;
	t_sign_type	sign_type;
	char		*formated;
	t_pipes		*last_node;

	i = 0;
	while (input[i])
	{
		formated = trim_str(input, &sign_type, &i, status);
		add_to_list(head, formated, status, init);
		last_node = find_last_node(*head);
		last_node->pipe_type = sign_type;
		if (!input[i])
			break ;
		else if (input[i + 1] && (input[i + 1] == '|' || input[i + 1] == '&'))
			i += 2;
		else
			i++;
	}
}

static void	add_to_list(t_pipes **head, char *formated, int status, \
t_init *init)
{
	t_pipes		*next_node;
	t_pipes		*last_node;
	t_pipes		*down_node;
	char		*formated_parenthesis;

	formated_parenthesis = create_str_bet_parent(formated);
	down_node = NULL;
	if (formated_parenthesis)
	{
		creat_list(&down_node, formated_parenthesis, init, 1);
		free(formated_parenthesis);
	}
	else if (status == 1)
		creat_list(&down_node, formated, init, 0);
	next_node = malloc(sizeof(t_pipes));
	if (!next_node)
		return ;
	last_node = find_last_node(*head);
	if (!last_node)
		*head = next_node;
	else
		last_node->next = next_node;
	next_node->input_string = formated;
	init_node(next_node, down_node, init);
}
