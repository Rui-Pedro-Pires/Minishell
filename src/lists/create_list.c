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

static void	add_list(t_pipes **head, char *formated, t_sign_type pipe_type, t_init init);
static char	*create_str_bet_parent(char *formated);
static void	bet_parent_count(char *formated, int *x);
static void	bet_parent_add(char *formated, char **bet_parent, int x, int i);

void	creat_list(t_pipes **head, char *input, t_init init)
{
	int			i;
	t_sign_type	sign_type;
	char		*formated;

	i = 0;
	while (input[i])
	{
		formated = trim_str(input, &sign_type, &i);
		add_list(head, formated, sign_type, init);
		if (!input[i])
			break ;
		else if (input[i + 1] && (input[i + 1] == '|' || input[i + 1] == '&'))
			i += 2;
		else
			i++;
	}
}

static void	add_list(t_pipes **head, char *formated, t_sign_type sign_type, t_init init)
{
	t_pipes		*next_node;
	t_pipes		*last_node;
	t_pipes		*down_node;
	char		*formated_parenthesis;

	formated_parenthesis = create_str_bet_parent(formated);
	down_node = NULL;
	if (formated_parenthesis)
	{
		creat_list(&down_node, formated_parenthesis, init);
		free(formated_parenthesis);
	}
	next_node = malloc(sizeof(t_pipes));
	if (!next_node)
		return ;
	last_node = find_last_node(*head);
	if (!last_node)
		*head = next_node;
	else
		last_node->next = next_node;
	next_node->input_string = formated;
	next_node->pipe_type = sign_type;
	next_node->heardocs = init.heardoc_read;
	next_node->envs = init.envs;
	next_node->sorted_envs =  init.sorted_envs;
	next_node->next = NULL;
	next_node->down = down_node;
}

static char	*create_str_bet_parent(char *formated)
{
	char	*formated_parenthesis;
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (formated[i] && formated[i] == ' ')
		i++;
	if (formated[i] != '(')
		return (NULL);
	i++;
	x = i;
	bet_parent_count(formated, &x);
	formated_parenthesis = ft_calloc(sizeof(char), x - i + 1);
	x = 0;
	bet_parent_add(formated, &formated_parenthesis, x, i);
	return (formated_parenthesis);
}

static void	bet_parent_count(char *formated, int	*x)
{
	int	parenthesis_num;

	parenthesis_num = 1;
	while (formated[(*x)])
	{
		if (formated[(*x)] == '(')
			parenthesis_num++;
		else if (formated[(*x)] == ')')
			parenthesis_num--;
		if (parenthesis_num == 0)
			break ;
		(*x)++;
	}
}

static void	bet_parent_add(char *formated, char **bet_parent, int x, int i)
{
	int	parenthesis_num;

	parenthesis_num = 1;
	while (formated[i])
	{
		if (formated[i] == '(')
			parenthesis_num++;
		else if (formated[i] == ')')
			parenthesis_num--;
		if (parenthesis_num == 0)
			break ;
		(*bet_parent)[x] = formated[i];
		x++;
		i++;
	}
}
