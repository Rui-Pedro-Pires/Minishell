/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_in_out.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:16:54 by ruiolive          #+#    #+#             */
/*   Updated: 2024/04/06 12:58:15 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	define_input_and_output(t_pipes *node)
{
	int		i;

	i = 0;
	while (node->input_string[i])
	{
		heardoc(node, i);
		redirect_input(node, i);
		if (append_output(node, i) != 0)
			return (1);
		if (redir_pipe(node, i) != 0)
			return (1);
		if (redirect_output(node, i) != 0)
			return (1);
		else
		{
			if (node->input_string[i])
				i += all_quotes_ignore(node->input_string + i);
		}
	}
	if (node->in_out.input_type == REDIRECT_INPUT)
		return (redirect_input_case(node));
	return (0);
}
