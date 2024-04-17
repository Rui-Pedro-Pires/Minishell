/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_search_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive  <ruiolive@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:55:20 by ruiolive          #+#    #+#             */
/*   Updated: 2024/02/05 11:55:20 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*search_char(char *input)
{
	int	i;

	i = 0;
	while (input[i] && ft_strchr(" \t\n", input[i]))
		i++;
	if (input[i] && (input[i] == '>' || input[i] == '<'))
		return (signs_search(input + i));
	if (input[i] && (input[i] == '|' || input[i] == '&'))
		return (pipe_amper_search(input + i));
	if (input[i] && (input[i] == '(' || input[i] == ')'))
		return (parenthesis_search(input + i));
	return (0);
}

char	*signs_search(char *input)
{
	int	i;

	i = 0;
	if (input[i] && input[i] == '>')
	{
		if (input[++i] && input[i] == '>')
			return (">>");
		return (">");
	}
	if (input[i] && input[i] == '<')
	{
		if (input[++i] && input[i] == '<')
			return ("<<");
		return ("<");
	}
	return (NULL);
}

char	*pipe_amper_search(char *input)
{
	int	i;

	i = 0;
	if (input[i] && input[i] == '|')
	{
		i++;
		if (input[i] && input[i] == '|')
			return ("||");
		if (input[i] && input[i] == '&')
			return ("|&");
		return ("|");
	}
	if (input[i] && input[i] == '&')
	{
		if (input[++i] && input[i] == '&')
			return ("&&");
		return ("&");
	}
	return (NULL);
}

char	*parenthesis_search(char *input)
{
	int	i;

	i = 0;
	if (input[i] && input[i] == '(')
	{
		if (input[++i] && input[i] == '(')
			return ("((");
		return ("(");
	}
	if (input[i] && input[i] == ')')
	{
		if (input[++i] && input[i] == ')')
			return ("))");
		return (")");
	}
	return (NULL);
}
