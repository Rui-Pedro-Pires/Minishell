/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_in_out_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive  <ruiolive@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 20:17:32 by ruiolive          #+#    #+#             */
/*   Updated: 2024/02/29 20:17:32 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*search_file_name(char *str)
{
	int		i;
	int		x;
	char	*file_name;

	i = 1;
	while (str[i] && str[i] == ' ')
		i++;
	x = i;
	while (str[x] && !ft_strchr("<> ", str[i]))
		x++;
	file_name = malloc(sizeof(char) * x - i + 1);
	x = 0;
	while (str[i] && !ft_strchr("<> ", str[i]))
	{
		file_name[x] = str[i];
		x++;
		i++;
	}
	file_name[x] = '\0';
	return (file_name);
}

int	redirect_output_case(t_pipes *node, int i)
{
	int	fd;

	node->in_out.output_type = REDIRECT_OUTPUT;
	if (node->in_out.output_file)
	{
		free(node->in_out.output_file);
		node->in_out.output_file = NULL;
	}
	node->in_out.output_file = search_file_name(node->input_string + i);
	fd = open(node->in_out.output_file, O_CREAT, 0660);
	if (fd < 0)
		return (0);
	close(fd);
	unlink(node->in_out.output_file);
	fd = open(node->in_out.output_file, O_CREAT, 0660);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	append_output_case(t_pipes *node, int i)
{
	int	fd;

	node->in_out.output_type = APPEND_OUTPUT;
	if (node->in_out.output_file)
	{
		free(node->in_out.output_file);
		node->in_out.output_file = NULL;
	}
	node->in_out.output_file = search_file_name(node->input_string + i + 1);
	fd = open(node->in_out.output_file, O_CREAT | O_RDWR, 0660);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	redirect_input_case(t_pipes *node)
{
	int		fd;
	char	*buffer;

	fd = open(node->in_out.input_file, O_RDONLY);
	if (fd < 0)
	{
		perror("minishell");
		free(node->in_out.input_file);
		node->in_out.input_file = NULL;
		return (0);
	}
	buffer = ft_calloc(sizeof(char), 5);
	node->in_out.data_read = ft_strdup("");
	while (1)
	{
		if (read(fd, buffer, 4) <= 0)
			break ;
		node->in_out.data_read = ft_strjoin_free(node->in_out.data_read, \
		buffer);
	}
	free(buffer);
	free(node->in_out.input_file);
	node->in_out.input_file = NULL;
	close(fd);
	return (1);
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
		x++;
	new_str_size = ft_strlen(str) - (x - i) + 1;
	new_str = ft_calloc(sizeof(char), new_str_size);
	while (++itr < i)
		new_str[itr] = str[itr];
	while (str[x])
		new_str[itr++] = str[x++];
	free(str);
	node->input_string = new_str;
}
