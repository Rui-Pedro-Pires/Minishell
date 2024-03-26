/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:43:48 by ruiolive          #+#    #+#             */
/*   Updated: 2024/03/26 10:28:12 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_for_dbpipe_dbamper(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if ((input[i] == '|' && input[i + 1] == '|') || input[i] == '&')
			return (1);
		i++;
	}
	return (0);
}

void	init_node(t_pipes *next_node, t_pipes *down_node, \
t_sign_type sign_type, t_init init)
{
	next_node->pipe_type = sign_type;
	next_node->init = init;
	next_node->skip = false;
	next_node->next = NULL;
	next_node->down = down_node;
	next_node->init.return_value = 0;
}

void	define_pipe_type(char *input, t_sign_type *sign_type, int *i)
{
	if (!input[(*i)])
		*sign_type = N_PIPE;
	else if (input[(*i) + 1] && input[(*i) + 1] == '|')
		*sign_type = D_PIPE;
	else if (input[(*i)] && input[(*i)] == '|')
		*sign_type = S_PIPE;
	else if (input[(*i)] && input[(*i)] == '&')
		*sign_type = AMPER;
}

t_pipes	*find_last_node(t_pipes *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}
