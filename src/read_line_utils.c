/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:36:21 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/31 15:26:06 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	count_parenthesis(char *input, int *parenthesis, int *check_empty)
{
	int	i;

	i = 0;
	if (!input || !(*input))
		return (1);
	while (input[i])
	{
		if (!ft_strchr("|<>&()", input[i]))
			(*check_empty) = 0;
		if (input[i] == D_QUOTES)
			i += quotes_check(input + i, D_QUOTES);
		else if (input[i] == S_QUOTES)
			i += quotes_check(input + i, S_QUOTES);
		if (input[i] && input[i] == '(')
		{
			if (!check_for_command_before(input, i))
				return (error_handler(ERROR_NEWLINE, &"newline", NULL), 0);
			(*parenthesis)++;
			(*check_empty) = 1;
		}
		else if (input[i] && input[i] == ')' && (*check_empty) == 0)
			(*parenthesis)--;
		if ((input[i] && input[i] == ')' \
		&& (*check_empty) == 1) || (*parenthesis) < 0)
			return (error_handler(ERROR_SPECIAL_CHAR, &")", NULL), 0);
		i++;
	}
	return (1);
}

char	*ft_strjoin_v2(char *s1, char *s2)
{
	char	*new_str;
	int		i;
	int		n;

	new_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!new_str)
		return (NULL);
	i = 0;
	n = 0;
	while (s1[i] != '\0')
		new_str[n++] = s1[i++];
	i = 0;
	new_str[n++] = ' ';
	while (s2[i] != '\0')
		new_str[n++] = s2[i++];
	new_str[n] = '\0';
	free(s1);
	free(s2);
	return (new_str);
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

static char	*trim_cwd(char *trimmed_cwd)
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
			break;
		i++;
	}
	trimmed = ft_substr(trimmed_cwd, i, (ft_strlen(trimmed_cwd) - i));
	free(trimmed_cwd);
	return (trimmed);
}

int	check_for_command_before(char *input, int i)
{
	if (i == 0)
		return (1);
	i--;
	if (i >= 0 && input[i] == '*')
		return (1);
	while (i >= 0 && input[i] == ' ')
		i--;
	if (input[i] && ft_strchr("|&<>()", input[i]))
		return (1);
	return (0);
}
