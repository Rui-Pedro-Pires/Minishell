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

#include "../includes/minishell.h"

static void	redirect_output_case(t_pipes *node, int i);
static int	redirect_input_case(t_pipes *node, int i);
static void	append_output_case(t_pipes *node, int i);
static void	rechange_str(t_pipes *node, int i, int to_skip);

int define_in_out(t_pipes *node)
{
	int		i;

	i = 0;
	while (node->input_string[i])
	{
		if (!ft_strncmp(node->input_string + i, "<<", 2))
		{
			node->in_out.input_type = HEARDOC;
			node->init.heardoc_index++;
			rechange_str(node, i, 2);
		}
		else if (node->input_string[i] == '<')
		{
			redirect_input_case(node, i);
			rechange_str(node, i, 1);
		}
		if (!ft_strncmp(node->input_string + i, ">>", 2))
		{
			append_output_case(node, i);
			rechange_str(node, i, 2);
		}
		else if (!ft_strncmp(node->input_string + i, ">|", 2))
		{
			redirect_output_case(node, i + 1);
			rechange_str(node, i, 2);
		}
		else if (node->input_string[i] == '>')
		{
			redirect_output_case(node, i);
			rechange_str(node, i, 1);
		}
		else
			i++;
	}
	return (1);
}

static void	redirect_output_case(t_pipes *node, int i)
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
	{
		i++;
		return ;
	}
	unlink(node->in_out.output_file);
	fd = open(node->in_out.output_file, O_CREAT, 0660);
	close(fd);
}

static void	append_output_case(t_pipes *node, int i)
{
	int fd;

	node->in_out.output_type = APPEND_OUTPUT;
	if (node->in_out.output_file)
	{
		free(node->in_out.output_file);
		node->in_out.output_file = NULL;
	}
	node->in_out.output_file = search_file_name(node->input_string + i + 1);
	fd = open(node->in_out.output_file, O_CREAT | O_RDWR, 0660);
	close(fd);
}

static int	redirect_input_case(t_pipes *node, int i)
{
	int	fd;
	char	*buffer;

	buffer = NULL;
	node->in_out.input_type = REDIRECT_INPUT;
	if (node->in_out.input_file)
	{
		free(node->in_out.input_file);
		node->in_out.input_file = NULL;
	}
	node->in_out.input_file = search_file_name(node->input_string + i);
	fd = open(node->in_out.input_file, O_RDONLY);
	if (fd < 0)
	{
		printf("minishell: %s: No such file or directory\n", node->in_out.input_file);
		return (0);
	}
	buffer = ft_calloc(sizeof(char), 101);
	node->in_out.data_read = ft_strdup("");
	while (1)
	{
		if (read(fd, buffer, 100) <= 0)
			break ;
		node->in_out.data_read = ft_strjoin_free(node->in_out.data_read, buffer);
	}
	free(buffer);
	close(fd);
	return (1);
}

static void	rechange_str(t_pipes *node, int i, int to_skip)
{
	int		x;
	int		itr;
	int		new_str_size;
	char	*str;
	char 	*new_str;

	itr = -1;
	str = node->input_string;
	x = i + to_skip;
	while (str[x] && str[x] == ' ')
		x++;
	while (str[x] && !ft_strchr(" <>", str[x]))
		x++;
	new_str_size = ft_strlen(str) - (x - i) + 1;
	new_str = malloc(sizeof(char) * new_str_size);
	while (++itr < i)
		new_str[itr] = str[itr];
	while (str[x])
	{
		new_str[itr] = str[x];
		x++;
		itr++;
	}
	new_str[itr] = '\0';
	free(str);
	node->input_string = new_str;
}
