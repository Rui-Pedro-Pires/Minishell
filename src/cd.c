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
	char	*current_dir;
	char	*new_dir;

	current_dir = getcwd(NULL, 0);
	printf("current directory: %s\n", current_dir);
	new_dir = get_new_dir(str);
	if (chdir(new_dir) == (-1))
	{
		err_num_chdir(new_dir);
		return ;
	}
	current_dir = getcwd(NULL, 0);
	printf("new directory: %s\n", current_dir);
	// free(new_dir);
	// free(current_dir);
}

char	*get_new_dir(char *str)
{
	if (strcmp(str, "") == 0 || strcmp(str, "~") == 0 || str == NULL)
		return (getenv("HOME"));
	str = check_quotes_n_expand(str);
	return (str);
}

void	err_num_chdir(char *str)
{
	if (errno = ENOENT)
		printf("\nruiolive&&jorteixe@minishell: cd: %s: No such file or directory\n", str);
	else if (errno = ENOTDIR)
		printf("\nruiolive&&jorteixe@minishell: cd: %s: Not a directory\n", str);
}
