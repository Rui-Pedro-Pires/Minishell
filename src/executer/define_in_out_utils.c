/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heardoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:55:58 by ruiolive          #+#    #+#             */
/*   Updated: 2024/04/06 12:17:35 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*search_file_name(t_pipes *node, char *str)
{
	int		i;
	int		x;
	int		j;
	char	*file_name;

	i = 1;
	while (str[i] && str[i] == ' ')
		i++;
	x = i;
	while (str[x] && !ft_strchr("<> ", str[x]))
		x += all_quotes_ignore(str + x);
	file_name = ft_calloc(sizeof(char), x - i + 1);
	j = 0;
	x = x - i;
	while (j < x)
	{
		file_name[j] = str[i];
		j++;
		i++;
	}
	file_name = check_quotes_n_expand(*node->init, file_name);
	return (file_name);
}

int	redirect_output_case(t_pipes *node, int i)
{
	char	*file_name;

	node->in_out.output_type = REDIRECT_OUTPUT;
	file_name = search_file_name(node, node->input_string + i);
	node->in_out.fd_out = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (node->in_out.fd_out < 0)
	{
		print_error("minishell: ");
		perror(file_name);
		free(file_name);
		return (1);
	}
	free(file_name);
	return (0);
}

int	append_output_case(t_pipes *node, int i)
{
	char	*file_name;

	node->in_out.output_type = APPEND_OUTPUT;
	file_name = search_file_name(node, node->input_string + i + 1);
	node->in_out.fd_out = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (node->in_out.fd_out < 0)
	{
		print_error("minishell: ");
		perror(file_name);
		free(file_name);
		return (1);
	}
	free(file_name);
	return (0);
}

void	rechange_str(t_pipes *node, int i, int to_skip)
{
	int		x;
	int		itr;
	int		new_str_size;
	char	*str;
	char	*new_str;

	itr = -1;
	str = node->input_string;
	x = i + to_skip;
	while (str[x] && str[x] == ' ')
		x++;
	while (str[x] && !ft_strchr(" <>", str[x]))
		x += all_quotes_ignore(str + x);
	new_str_size = ft_strlen(str) - (x - i) + 1;
	new_str = ft_calloc(sizeof(char), new_str_size);
	while (++itr < i)
		new_str[itr] = str[itr];
	while (str[x])
		new_str[itr++] = str[x++];
	free(str);
	node->input_string = new_str;
}
