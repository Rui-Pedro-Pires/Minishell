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

#include "../includes/minishell.h"

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
			break;
		i++;
	}
	trimmed = ft_substr(trimmed_cwd, i, (ft_strlen(trimmed_cwd) - i));
	free(trimmed_cwd);
	return (trimmed);
}

char *get_input(void)
{
	char	*cwd;
	char    *input;

	cwd = creat_cwd();
	input = readline(cwd);
	free(cwd);
	return (input);
}
