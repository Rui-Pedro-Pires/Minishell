/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:36:21 by ruiolive          #+#    #+#             */
/*   Updated: 2024/02/01 10:16:39 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*trim_cwd(char *trimmed_cwd);

int	unfinished_command_line(char *input)
{
	int	i;

	i = 0;
	if (!input || !(*input))
		return (0);
	while (input[i + 1])
		i++;
	while (i >= 0 && input[i] == ' ')
		i--;
	if (input[i] == '|' || input[i] == '&')
		return (1);
	return (0);
}

char	*creat_cwd(void)
{
	char	*cwd;
	char	*cwd_complete;
	char	*trimmed_cwd;

	trimmed_cwd = getcwd(NULL, 0);
	trimmed_cwd = trim_cwd(trimmed_cwd);
	cwd = ft_strjoin("ruiolive&&jorteixe@minishell:~", trimmed_cwd);
	cwd_complete = ft_strjoin(cwd, "$ ");
	free(cwd);
	free(trimmed_cwd);
	return (cwd_complete);
}

char	*trim_cwd(char *trimmed_cwd)
{
	int		i;
	int		counter;
	char	*trimmed;

	i = 0;
	counter = 0;
	while (trimmed_cwd[i])
	{
		if (trimmed_cwd[i] == '/')
			counter++;
		if (counter > 3)
			break ;
		i++;
	}
	trimmed = ft_substr(trimmed_cwd, i, (ft_strlen(trimmed_cwd) - i));
	free(trimmed_cwd);
	return (trimmed);
}
