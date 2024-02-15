/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:07:37 by jorteixe          #+#    #+#             */
/*   Updated: 2024/02/05 16:15:29 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(char *str)
{
	char	*new_dir;
	if (strcmp(str, "") == 0 || strcmp(str, "~") == 0 || str == NULL)
		new_dir = getenv("HOME");
	else
	 new_dir = check_quotes_n_expand(str);
	if (chdir(new_dir) == (-1))
	{
		err_num_chdir(new_dir);
		free(new_dir);
		return ;
	}
	free(new_dir);
}

void	err_num_chdir(char *str)
{
	if (errno == ENOENT)
		printf("\nruiolive&&jorteixe@minishell: cd: %s: No such file or directory\n", str);
	else if (errno == ENOTDIR)
		printf("\nruiolive&&jorteixe@minishell: cd: %s: Not a directory\n", str);
}
