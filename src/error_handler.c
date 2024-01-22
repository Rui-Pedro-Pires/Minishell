/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:57:37 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/22 15:57:47 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_handler(int error_msg, void *param, void **param2)
{
	if (error_msg == ERROR_UNFINISHED_QUOTE)
	{
		(void)param2;
		printf("Unfinished Quote\n");
		free(param);
	}
	exit(1);
}