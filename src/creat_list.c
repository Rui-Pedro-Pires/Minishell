/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:43:48 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/22 15:49:36 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_data   *find_last_node(t_data *head);
static void    add_list(t_data **head, char *formated, int pipe_type);
static char    *trim_str(char *input, int *pipe_check);

void    creat_list(t_data **head, char *input)
{
    int			i;
    int		pipe_type;
    char	*formated;
    
    i = 0;
    while (input[i])
    {
        formated = trim_str(input + i, &pipe_type);
        add_list(head, formated, pipe_type);
        while (input[i] != '|' && input[i + 1])
		i++;
	if (input[i + 1] == '|' && input[i + 2])
		i += 2;
	else
		i++;
	
    }
}

static void    add_list(t_data **head, char *formated, int pipe_type)
{
    t_data  *new_node;
    t_data  *last_node;

    new_node = malloc(sizeof(t_data));
    if (!new_node)
        return ;
    last_node = find_last_node(*head);
    if (!last_node)
        *head = new_node;
    else
        last_node->next = new_node;
    new_node->cmd = formated;
    new_node->pipe_type = pipe_type;
    new_node->next = NULL;
}

static t_data   *find_last_node(t_data *head)
{
    if (!head)
        return (NULL);
    while (head->next)
        head = head->next;
    return (head);
}

static char    *trim_str(char *input, int *pipe_check)
{
    	int 		i;
	int		x;
   	char	*formated;
    
   	i = 0;
	x = 0;
   	while (input[i] != '|' && input[i])
		i++;
	formated = malloc(sizeof(char) * i + 1);
	if (!formated)
		return (NULL);
	if (input[i + 1] && input[i + 1] == '|')
		*pipe_check = D_PIPE;
	else if (!input[i] || input[i + 1] != '|')
		*pipe_check = S_PIPE;
	i = 0;
	while (input[i] != '|')
	{
		formated[x] = input[i];
		x++;
		i++;
	}
	formated[x] = '\0';
	return (formated);
}
