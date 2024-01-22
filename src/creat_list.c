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
static void    add_list(t_data **head, char c);

void    creat_list(t_data **head, char *input)
{
    int i;

    i = 0;
    while (input[i])
    {
        add_list(head, input[i]);
        i++;
    }
}

static void    add_list(t_data **head, char c)
{
    t_data  *new_node;
    t_data  *last_node;

    (void)c;
    new_node = malloc(sizeof(t_data));
    if (!new_node)
        return ;
    last_node = find_last_node(*head);
    if (!last_node)
        *head = new_node;
    else
        last_node->next = new_node;
    new_node->c = c;
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
