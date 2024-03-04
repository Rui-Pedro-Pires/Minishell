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

static void	redirect_output_case(t_pipes *node, int *i);
static int	redirect_input_case(t_pipes *node, int *i);
static void	append_output_case(t_pipes *node, int *i);
static void	heardoc_case(t_pipes *node, int *i);

int define_in_out(t_pipes *node)
{
	int				i;

	i = 0;
	node->in_out.input_type = NO_INPUT;
	node->in_out.output_type = NO_OUTPUT;
	node->in_out.output_file = NULL;
	node->in_out.input_file = NULL;
	while (node->input_string[i])
	{
		if (!ft_strncmp(node->input_string + i, "<<", 2))
			heardoc_case(node, &i);
		else if (node->input_string[i] == '<')
		{
				if (!redirect_input_case(node, &i))
				return (0);
		}
		if (!ft_strncmp(node->input_string + i, ">>", 2))
			append_output_case(node, &i);
		else if (node->input_string[i] == '>')
			redirect_output_case(node, &i);
		else
			i++;
	}
	return (1);
}

static void	redirect_output_case(t_pipes *node, int *i)
{
	int	fd;

	node->in_out.output_type = REDIRECT_OUTPUT;
	if (node->in_out.output_file)
	{
		free(node->in_out.output_file);
		node->in_out.output_file = NULL;
	}
	node->in_out.output_file = search_file_name(node->input_string + *i);
	unlink(node->in_out.output_file);
	fd = open(node->in_out.output_file, O_CREAT, 0660);
	close(fd);
	(*i)++;
}

static void	append_output_case(t_pipes *node, int *i)
{
	int fd;

	node->in_out.output_type = APPEND_OUTPUT;
	if (node->in_out.output_file)
	{
		free(node->in_out.output_file);
		node->in_out.output_file = NULL;
	}
	node->in_out.output_file = search_file_name(node->input_string + *i + 1);
	fd = open(node->in_out.output_file, O_CREAT | O_RDWR, 0660);
	close(fd);
	(*i) += 2;
}

static int	redirect_input_case(t_pipes *node, int *i)
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
	node->in_out.input_file = search_file_name(node->input_string + *i);
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
	(*i)++;
	return (1);
}

static void	heardoc_case(t_pipes *node, int *i)
{
	node->in_out.input_type = HEARDOC;
	node->init.heardoc_index++;
	(*i) += 2;
}