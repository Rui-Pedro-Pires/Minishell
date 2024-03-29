/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:55:35 by ruiolive          #+#    #+#             */
/*   Updated: 2024/03/29 14:19:10 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int    init_data(t_pipes *node)
{
    int    i;
    int		status;

    node->in_out.input_type = NO_INPUT;
    node->in_out.output_type = NO_OUTPUT;
    node->in_out.output_file = NULL;
    node->in_out.input_file = NULL;
    status = define_input_and_output(node);
    node->data.command_n_args = ft_split_ignore_quotes(node->input_string, " \t\n");

    i = 0;
    while (node->data.command_n_args[i] != NULL)
    {
        node->data.command_n_args[i] = check_quotes_n_expand(node,
                node->data.command_n_args[i]);
        i++;
    }
    command_decider(node);
    return (status);
}
