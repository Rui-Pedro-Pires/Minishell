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

#include "../../../includes/minishell.h"

void	update_old_pwd(t_envs *head);

int	ft_cd(t_envs *head, char **str)
{
	char	*new_dir;

	update_old_pwd(head);
	if (str[1] == NULL)
	{
		new_dir = ft_getenv(head, "HOME");
		chdir(new_dir);
		free(new_dir);
		new_dir = NULL;
		return (1);
	}
	if (str[2] != NULL)
		return (printf("\nruiolive&&jorteixe@minishell: cd: too many arguments\n"), 0);
	else
	{
		if (strcmp(str[1], "") == 0 || strcmp(str[1], "~") == 0
			|| str[1] == NULL)
			new_dir = ft_getenv(head, "HOME");
		else
			new_dir = ft_strdup(str[1]);
		if (chdir(new_dir) == (-1))
		{
			err_num_chdir(new_dir);
			free(new_dir);
			new_dir = NULL;
			return (0);
		}
		free(new_dir);
	}
	return (1);
}

void	err_num_chdir(char *str)
{
	if (errno == ENOENT)
		printf("\nruiolive&&jorteixe@minishell:"
			"cd: %s: No such file or directory\n",
			str);
	else if (errno == ENOTDIR)
		printf("\nruiolive&&jorteixe@minishell: cd: %s: Not a directory\n",
			str);
}

void	update_old_pwd(t_envs *head)
{
	char	*old_dir;
	char	*name;
	char	*str_array[2];
	char	*total;
	int		total_size;

	old_dir = getcwd(NULL, 0);
	name = "OLDPWD=";
	total_size = ft_strlen(name) + ft_strlen(old_dir) + 1;
	total = malloc(total_size);
	ft_strlcpy(total, name, ft_strlen(name) + 1);
	ft_strlcat(total, old_dir, total_size);
	str_array[0] = NULL;
	str_array[1] = total;
	str_array[2] = NULL;
	ft_export(head, str_array);
	free(total);
	free(old_dir);
}
