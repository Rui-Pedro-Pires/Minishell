/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:57:37 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/31 15:27:37 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_handler(int error_msg, void *param, void **param2)
{
	if (error_msg == ERROR_UNFINISHED_QUOTE)
	{
		(void)param2;
		printf("minishell: syntax error near unexpected token `%c'\n",
			*(char *)param);
	}
	else if (error_msg == ERROR_SPECIAL_CHAR)
	{
		(void)param2;
		printf("minishell: syntax error near unexpected token `%c'\n",
			*(char *)param);
	}
	else if (error_msg == ERROR_SPECIAL_CHAR_DOUBLE)
	{
		printf("minishell: syntax error near unexpected token `%c%c'\n",
			*(char *)param, *(char *)param);
	}
	else if (error_msg == ERROR_NEWLINE)
	{
		(void)param2;
		printf("minishell: syntax error near unexpected token `%s'\n",
			(char *)param);
	}
	else if (error_msg == ERROR_STRING_TYPE)
	{
		(void)param2;
		printf("minishell: syntax error near unexpected token `%s'\n",
			(char *)param);
	}
}
