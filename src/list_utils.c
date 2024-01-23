/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:43:48 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/23 15:09:11 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_pipes	*find_last_node(t_pipes *head);
static void		add_list(t_pipes **head, char *formated, t_type_pipe pipe_type);
<<<<<<< HEAD

void	creat_list(t_pipes **head, char *input)
{
	int			i;
	t_type_pipe	pipe_type;
	char		*formated;
=======
static void		check_last_node(t_pipes **head);

void	creat_list(t_pipes **head, char *input)
{
	int					i;
	t_type_pipe			pipe_type;
	char				*formated;
>>>>>>> 481c3d9294aab4d2978077f6e7e800c53b803bd3

	i = 0;
	while (input[i])
	{
		formated = trim_str(input + i, &pipe_type);
		add_list(head, formated, pipe_type);
<<<<<<< HEAD
		while (input[i] != '|' && input[i])
=======
		while (input[i] && input[i] != '|')
>>>>>>> 481c3d9294aab4d2978077f6e7e800c53b803bd3
		{
			if (input[i] == D_QUOTES)
				i += quotes_check(input + i, D_QUOTES);
			else if (input[i] == S_QUOTES)
				i += quotes_check(input + i, S_QUOTES);
			else
				i++;
		}
<<<<<<< HEAD
		if (input[i + 1] == '|' && input[i + 2])
=======
		if (input[i + 1] && input[i + 1] == '|')
>>>>>>> 481c3d9294aab4d2978077f6e7e800c53b803bd3
			i += 2;
		else
			i++;
	}
<<<<<<< HEAD
=======
	check_last_node(head);
>>>>>>> 481c3d9294aab4d2978077f6e7e800c53b803bd3
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

<<<<<<< HEAD
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
=======
static void	check_last_node(t_pipes **head)
{
	if ((find_last_node(*head))->pipe_type == D_PIPE \
	|| (find_last_node(*head))->pipe_type == S_PIPE)
		add_list(head, NULL, N_PIPE);
>>>>>>> 481c3d9294aab4d2978077f6e7e800c53b803bd3
}
