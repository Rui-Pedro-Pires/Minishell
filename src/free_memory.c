/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:57:46 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/30 14:18:46 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	coador(t_pipes **head)
{
	int		i;
	t_pipes	*tail;

	while ((*head))
	{
		i = 0;
		tail = (*head)->next;
		while ((*head)->data[i].command_n_args)
		{
			free_args((*head)->data[i].command_n_args);
			i++;
		}
		free((*head)->data);
		free(*head);
		(*head) = tail;
	}
}

void	freezzzz(char *input, char ***heardoc_read)
{
	int	i;

	i = 0;
	free(input);
	if (!(*heardoc_read))
		return ;
	while ((*heardoc_read)[i])
	{
		free((*heardoc_read)[i]);
		i++;
	}
	free((*heardoc_read));
	(*heardoc_read) = NULL;
}
