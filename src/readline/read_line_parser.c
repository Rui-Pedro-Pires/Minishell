/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:14:26 by ruiolive          #+#    #+#             */
/*   Updated: 2024/02/01 10:22:46 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_separator_before(char *input, int i)
{
	if (i == 0)
		return (1);
	i--;
	while (i >= 0 && input[i] == ' ')
		i--;
	if (input[i] && ft_strchr("|&<>()", input[i]))
		return (1);
	return (0);
}

int	check_separator_after(char *input, int i)
{
	if (!input[i])
		return (1);
	i++;
	while (input[i] && input[i] == ' ')
		i++;
	if (input[i] && ft_strchr("|&<>", input[i]))
		return (1);
	else if (!input[i])
		return (1);
	return (0);
}
