/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive  <ruiolive@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:16:54 by ruiolive          #+#    #+#             */
/*   Updated: 2024/02/29 11:16:54 by ruiolive         ###   ########.fr       */
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
			return (0);
		if (!redirect_input(node, i))
			return (0);
		if (!append_output(node, i))
			return (0);
		if (!redir_pipe(node, i))
			return (0);
		if (!redirect_output(node, i))
			return (0);
		else
		{
			if (node->input_string[i])
				i++;
		}
	}
	return (1);
}
