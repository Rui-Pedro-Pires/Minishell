/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 09:47:46 by jorteixe          #+#    #+#             */
/*   Updated: 2024/03/26 11:42:40 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		child_process(t_pipes *curr, t_pipes *head, int *fd, int i, int stdin);
void	loop_list_and_execute(t_pipes *curr, t_pipes *head, int size, int *status);
int		single_command(t_pipes *curr, t_pipes *head);

int	recursive_executer(t_pipes *current, int recursive, t_pipes *head)
{
	int		status;
	t_pipes	*curr;

	status = 0;
	curr = current;
	while (curr)
	{
		status = recursive_down(curr, head);
		if (status == 0 && curr->pipe_type == D_PIPE)
		{
			while (curr && curr->pipe_type != AMPER)
				curr = curr->next;
		}
		if (curr)
			curr = curr->next;
	}
	if (status != 0 && recursive == 1)
		return (status);
	return (status);
}

int	recursive_down(t_pipes *curr, t_pipes *head)
{
	int	status;

	if (!curr)
		return (-1);
	if (check_for_dbpipe_dbamper(curr->input_string))
		return (recursive_executer(curr->down, 1, head));
	status = recursive_down(curr->down, head);
	if (status != -1)
		return (status);
	return (list_iterator_executer(curr, head));
}

int	list_iterator_executer(t_pipes *curr, t_pipes *head)
{
	int	status;
	int	size;

	status = 0;
	(void)	head;	
	size = list_size(curr);
	if (size == 1)
		return (single_command(curr, head));
	loop_list_and_execute(curr, head, size, &status);
	return (status);
}

int	single_command(t_pipes *curr, t_pipes *head)
{
	int	status;
	int	pid;

	status = 0;
	if (init_data(curr) != 0)
		return (1);
	if (curr->data.command_type != CD && curr->data.command_type != EXIT)
	{
		pid = fork();
		if (pid == 0)
		{
			check_for_execution_to_file(curr, &status);
			ft_exit(head, status, NULL);
		}
		handle_sigint_status();
		wait(&status);
		if (status == 2)
			status = 33280;
		else if (status == 131)
			status = 33536;
		status = WEXITSTATUS(status);
	}
	else
		check_for_execution_to_file(curr, &status);
	return (status);
}

void	loop_list_and_execute(t_pipes *curr, t_pipes *head, int size, int *status)
{
	int	i;
	int	stdin;
	int	fd[2];

	i = 0;
	stdin = dup(STDIN_FILENO);
	curr->init->pid = malloc(sizeof(int) * size);
	while (curr)
	{
		curr->init->pid[i] = child_process(curr, head, fd, i, stdin);
		curr = curr->next;
		i++;
	}
	i = 0;
	close(stdin);
	handle_sigint_status();
	while (i < size)
	{
		if (i == size - 1)
			waitpid(head->init->pid[i], status, 0);
		else
			waitpid(head->init->pid[i], NULL, 0);
		i++;
	}
	free(head->init->pid);
	if (*status == 2)
		*status = 33280;
	else if (*status == 131)
		*status = 33536;
	*status = WEXITSTATUS(*status);
}

int	child_process(t_pipes *curr, t_pipes *head, int *fd, int i, int stdin)
{
	int	pid;
	int	status;

	status = 0;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		if (i != 0)
			dup2(stdin, STDIN_FILENO);
		if (curr->pipe_type == S_PIPE)
			dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		close(stdin);
		status = init_data(curr);
		if (status == 0)
			check_for_execution_to_file(curr, &status);
		ft_exit(head, status, NULL);
	}
	dup2(fd[0], stdin);
	close(fd[0]);
	close(fd[1]);
	return (pid);
}

int	execute_command(t_pipes *node)
{
	char	**args_array;
	int		cmd;

	args_array = node->data.command_n_args;
	cmd = node->data.command_type;
	if (cmd == ECHO)
		ft_echo(args_array);
	if (cmd == CD)
		return (ft_cd(node, args_array));
	if (cmd == PWD)
		ft_pwd();
	if (cmd == EXPORT)
		return (ft_export(node, args_array));
	if (cmd == UNSET)
		return (ft_unset(&node->init->envs, &node->init->sorted_envs,
				args_array), 0);
	if (cmd == ENV)
		return (ft_env(node->init->envs));
	if (cmd == EXIT)
		ft_exit(node, 1, args_array);
	if (cmd == NOT_BUILTIN)
		return (executens_ve(node));
	return (0);
}
