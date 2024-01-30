/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:36:21 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/30 14:48:03 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	unfinished_str(char *input)
{
	int	i;

	i = 0;
	if (!input || !(*input))
		return (0);
	while (input[i])
		i++;
	i--;
	while (i >= 0 && input[i] == ' ')
		i--;
	if (input[i] == '|' || input[i] == '&')
		return (1);
	return (0);
}

void	count_parenthesis(char *input, int *parenthesis)
{
	int	i;

	i = 0;
	if (!input || !(*input))
		return ;
	while (input[i])
	{
		if (input[i] == '(')
			(*parenthesis)++;
		else if (input[i] == ')')
			(*parenthesis)--;
		i++;
	}
}

int	parse_input(char *input)
{
	if (!check_unfinished_quotes(input)
		|| !wrong_specialch_syntax(input))
		return (0);
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
	char	*pwd;

	pwd = getcwd(NULL, 0);
	cwd = ft_strjoin("ruiolive&&jorteixe@minishell:", pwd);
	cwd_complete = ft_strjoin(cwd, "$ ");
	free(cwd);
	free(pwd);
	return (cwd_complete);
}
