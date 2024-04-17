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

static char	**ft_realloc(t_init *init, t_counter *iter);
static int	add_to_line(char **new_line, char *str, char **new_str,
				t_init init);
static void	child_process_heardoc(t_init *init, char *str_condition, int *fd);
static char	*process_heardoc(char *input, t_counter *iter, t_init *init);

int	heardoc_check(t_init *init, char *input, t_counter *itr, int i)
{
	char	*new_str;

	while (input[itr->i] && itr->i < i)
	{
		if (input[itr->i] && !ft_strncmp(input + itr->i, "<<", 2))
		{
			init->heardocs = ft_realloc(init, itr);
			new_str = process_heardoc(input, itr, init);
			if (!new_str && (g_return_value == 130 || g_return_value == 131))
			{
				free_args(init->heardocs);
				init->heardocs = NULL;
				return (0);
			}
			else if (!new_str)
				continue ;
			init->heardocs[itr->counter] = ft_strdup(new_str);
			free(new_str);
			itr->counter++;
		}
		itr->i += all_quotes_ignore(input + itr->i);
	}
	return (1);
}

static char	**ft_realloc(t_init *init, t_counter *iter)
{
	char	**copy;
	int		x;

	x = 0;
	copy = ft_calloc(sizeof(char *), (iter->counter + 2));
	if (!copy)
		return (NULL);
	if (!(init->heardocs))
		return (copy);
	while (init->heardocs[x])
	{
		copy[x] = ft_strdup(init->heardocs[x]);
		free(init->heardocs[x]);
		x++;
	}
	free(init->heardocs);
	return (copy);
}

static int	add_to_line(char **new_ln, char *str, char **new_str, t_init init)
{
	if (!(*new_ln))
		return (err_hlr_2(ERR_READ, str, NULL), 0);
	if (!(*(*new_ln)))
		return (free(*new_ln), 1);
	if (!ft_strncmp(*new_ln, str, maxlen(ft_strlen(*new_ln), ft_strlen(str))))
	{
		free(*new_ln);
		return (0);
	}
	else
	{
		*new_ln = expande_heardoc(init, *new_ln);
		*new_str = str_join_with_newline(*new_str, *new_ln);
	}
	return (1);
}

static char	*process_heardoc(char *input, t_counter *iter, t_init *init)
{
	int		fd[2];
	char	*str_condition;
	char	*new_str;
	int		status;

	str_condition = search_heardoc_condition(input, iter);
	if (!str_condition)
		return (NULL);
	str_condition = copy_inside_quotes(str_condition);
	pipe(fd);
	child_process_heardoc(init, str_condition, fd);
	update_sigint_status();
	wait(&status);
	status_update(status);
	close(fd[1]);
	if (status != 0)
	{
		free(str_condition);
		return (NULL);
	}
	new_str = read_heardoc_buffer(fd[0]);
	free(str_condition);
	return (new_str);
}

static void	child_process_heardoc(t_init *init, char *str_condition, int *fd)
{
	int		pid;
	char	*new_line;
	char	*new_str;

	pid = fork();
	if (pid == 0)
	{
		reset_sigint();
		free_args(init->heardocs);
		free_env_list(init->sorted_envs);
		close(fd[0]);
		new_str = ft_strdup("");
		while (1)
		{
			new_line = readline("> ");
			if (!add_to_line(&new_line, str_condition, &new_str, *init))
				break ;
		}
		free(str_condition);
		free_env_list(init->envs);
		write(fd[1], new_str, ft_strlen(new_str));
		free(new_str);
		exit(EXIT_SUCCESS);
	}
}
