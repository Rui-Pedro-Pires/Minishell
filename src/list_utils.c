/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:43:48 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/23 11:24:22 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_pipes	*find_last_node(t_pipes *head);
static void		add_list(t_pipes **head, char *formated, t_type_pipe pipe_type);

void	creat_list(t_pipes **head, char *input)
{
	int			i;
	t_type_pipe	pipe_type;
	char		*formated;

	i = 0;
	while (input[i])
	{
		formated = trim_str(input + i, &pipe_type);
		add_list(head, formated, pipe_type);
		while (input[i] != '|' && input[i])
		{
			if (input[i] == D_QUOTES)
				i += quotes_check(input + i, D_QUOTES);
			else if (input[i] == S_QUOTES)
				i += quotes_check(input + i, S_QUOTES);
			else
				i++;
		}
		if (input[i + 1] == '|' && input[i + 2])
			i += 2;
		else
			i++;
	}
}

static void	add_list(t_pipes **head, char *formated, t_type_pipe pipe_type)
{
	t_pipes	*new_node;
	t_pipes	*last_node;

	new_node = malloc(sizeof(t_pipes));
	if (!new_node)
		return ;
	last_node = find_last_node(*head);
	if (!last_node)
		*head = new_node;
	else
		last_node->next = new_node;
	new_node->input_string = formated;
	new_node->pipe_type = pipe_type;
	new_node->next = NULL;
}

static t_pipes	*find_last_node(t_pipes *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	organize_list(t_pipes *pipe_struct)
{
	int	count;

	count = 0;
	while (pipe_struct != NULL)
	{
		count = count_input(pipe_struct);
		pipe_struct->data = malloc(sizeof(t_data) * (count + 1));
		fill_data(pipe_struct, count);
		pipe_struct = pipe_struct->next;
	}
}
