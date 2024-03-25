/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_in_out.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:16:54 by ruiolive          #+#    #+#             */
/*   Updated: 2024/03/25 09:57:57 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	define_input_and_output(t_pipes *node)
{
	int		i;

	i = 0;
	while (node->input_string[i])
	{
		if (!heardoc(node, i))
			return (1);
		if (!redirect_input(node, i))
			return (1);
		if (!append_output(node, i))
			return (1);
		if (!redir_pipe(node, i))
			return (1);
		if (!redirect_output(node, i))
			return (1);
		else
		{
			if (node->input_string[i])
				i++;
		}
	}
	return (0);
}
