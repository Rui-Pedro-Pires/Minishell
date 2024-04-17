/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:36:46 by ruiolive          #+#    #+#             */
/*   Updated: 2024/04/06 12:17:42 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_input(t_init init);
static void	child_process_keep_reading(t_init *init, char *input,
				t_counter *c_struc, int *fd);
static void	ft_exit_keep_reading(t_init *init, char *input, int exit_type,
				bool add_to_history);

char	*line_read(t_init *init)
{
	char		*input;
	int			fd[2];
	t_counter	count_struc;

	count_struc.prnt = 0;
	count_struc.i = 0;
	count_struc.counter = 0;
	input = get_input(*init);
	if (!parse_input(input, &count_struc, init))
		return (add_history(input), free(input), NULL);
	input = keep_reading(input, &count_struc, init, fd);
	return (input);
}

static char	*get_input(t_init init)
{
	char	*cwd;
	char	*input;
	char	*pwd;

	cwd = creat_cwd();
	if (!cwd)
		create_cwd_from_envs(&pwd, &cwd, init);
	input = readline(cwd);
	if (!input)
	{
		free(cwd);
		printf("exit\n");
		free_env_list(init.envs);
		free_env_list(init.sorted_envs);
		exit(EXIT_SUCCESS);
	}
	free(cwd);
	return (input);
}

char	*keep_reading(char *input, t_counter *c_struc, t_init *init, int *fd)
{
	char	*buffer;
	int		status;

	if (unfinished_command_line(input) || c_struc->prnt > 0)
	{
		pipe(fd);
		child_process_keep_reading(init, input, c_struc, fd);
		update_sigint_status();
		wait(&status);
		status_update(status);
		close(fd[1]);
		if (status != 0)
			return (free(input), NULL);
		buffer = ft_calloc(sizeof(char), 2);
		free(input);
		input = ft_strdup("");
		while (1)
		{
			if (read(fd[0], buffer, 1) <= 0)
				break ;
			input = ft_strjoin_free(input, buffer);
		}
		free(buffer);
	}
	return (input);
}

static void	child_process_keep_reading(t_init *init, char *input,
		t_counter *c_struc, int *fd)
{
	char	*new_line;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		reset_sigint();
		close(fd[0]);
		while (unfinished_command_line(input) || c_struc->prnt > 0)
		{
			new_line = readline("> ");
			if (!new_line)
				ft_exit_keep_reading(init, input, 1, false);
			if (!(*new_line))
			{
				free(new_line);
				continue ;
			}
			input = str_join_with_space(input, new_line, 2);
			if (!parse_input(input, c_struc, init))
				ft_exit_keep_reading(init, input, 1, true);
		}
		write(fd[1], input, ft_strlen(input));
		ft_exit_keep_reading(init, input, 0, false);
	}
}

static void	ft_exit_keep_reading(t_init *init, char *input, int exit_type,
		bool add_to_history)
{
	if (add_to_history == true)
		add_history(input);
	free(input);
	free_args(init->heardocs);
	free_env_list(init->envs);
	free_env_list(init->sorted_envs);
	exit(exit_type);
}
