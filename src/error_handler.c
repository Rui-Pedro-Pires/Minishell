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

void	err_hlr_2(int error_msg, void *param, void **param2);
void	err_hndlr_3(int error_msg, void *param, void **param2);
void	err_hndlr_4(int error_msg, void *param, void **param2);

void	error_handler(int error_msg, void *param, void **param2)
{
	if (error_msg == ERROR_UNFINISHED_QUOTE)
	{
		(void)param2;
		print_error("minishell: syntax error near unexpected token `");
		print_error_char(*(char *)param);
		print_error("'\n");
		g_return_value = 2;
	}
	else if (error_msg == ERROR_SPECIAL_CHAR)
	{
		(void)param2;
		print_error("minishell: syntax error near unexpected token `");
		print_error_char(*(char *)param);
		print_error("'\n");
		g_return_value = 2;
	}
	else if (error_msg == ERROR_NEWLINE
		|| error_msg == ERROR_SPECIAL_CHAR_DOUBLE)
		err_hndlr_4(error_msg, param, param2);
}

void	err_hlr_2(int error_msg, void *param, void **param2)
{
	if (error_msg == ERR_WILDCARD)
	{
		(void)param2;
		print_error(" ambiguous redirect");
		print_error("\n");
		g_return_value = 1;
	}
	if (error_msg == ERR_STR)
	{
		(void)param2;
		print_error("minishell: syntax error near unexpected token `");
		print_error((char *)param);
		print_error("'\n");
		g_return_value = 2;
	}
	if (error_msg == ERR_READ)
	{
		(void)param2;
		print_error("minishell: warning: here-document ");
		print_error("delimited by end-of-file (wanted `");
		print_error((char *)param);
		print_error("')\n");
		g_return_value = 0;
	}
}

void	err_hndlr_3(int error_msg, void *param, void **param2)
{
	if (error_msg == ERR_STR_FREE)
	{
		(void)param2;
		if (!(*(char *)param) || !(char *)param)
		{
			print_error("minishell: syntax error near unexpected token `(");
			print_error("'\n");
		}
		else
		{
			print_error("minishell: syntax error near unexpected token `");
			print_error_char(*(char *)param);
			print_error("'\n");
		}
		free(param);
		g_return_value = 2;
	}
}

void	err_hndlr_4(int error_msg, void *param, void **param2)
{
	if (error_msg == ERROR_SPECIAL_CHAR_DOUBLE)
	{
		print_error("minishell: syntax error near unexpected token `");
		print_error_char(*(char *)param);
		print_error_char(*(char *)param);
		print_error("'\n");
		g_return_value = 2;
	}
	else if (error_msg == ERROR_NEWLINE)
	{
		(void)param2;
		print_error("minishell: syntax error near unexpected token `");
		print_error((char *)param);
		print_error("'\n");
		g_return_value = 2;
	}
}

char	*string_error(char *input)
{
	int		i;
	int		j;
	char	*error_str;

	i = 0;
	while (input[i] && input[i] == ' ')
		i++;
	j = i;
	while (input[j] && !ft_strchr("( ", input[j]))
		j++;
	error_str = malloc(sizeof(char) * (j - i) + 1);
	if (!error_str)
		return (NULL);
	j = 0;
	while (input[i] && !ft_strchr("( ", input[i]))
	{
		error_str[j] = input[i];
		j++;
		i++;
	}
	error_str[j] = '\0';
	return (error_str);
}
