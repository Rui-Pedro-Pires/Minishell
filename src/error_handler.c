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
}

void	err_hlr_2(int error_msg, void *param, void **param2)
{
	if (error_msg == ERR_STR)
	{
		(void)param2;
		printf("minishell: syntax error near unexpected token `%s'\n",
			(char *)param);
	}
	if (error_msg == ERR_READ)
	{
		(void)param2;
		printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n",
			(char *)param);
	}
	if (error_msg == ERR_STR_FREE)
	{
		(void)param2;
		if (!(*(char *)param) || !(char *)param)
			printf("minishell: syntax error near unexpected token `('\n");
		else
			printf("minishell: syntax error near unexpected token `%s'\n",
			(char *)param);
		free(param);
	}
}

char *string_error(char *input)
{
	int i;
	int j;
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
