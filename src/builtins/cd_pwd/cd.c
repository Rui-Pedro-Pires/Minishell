/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:07:37 by jorteixe          #+#    #+#             */
/*   Updated: 2024/04/05 19:29:42 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_cd(t_pipes *node, char **str)
{
	char	*new_dir;

	update_old_pwd(node);
	if (str[1] == NULL || str[1][0] == '~')
		return (handle_cd_home(node, str));
	if (str[2] != NULL)
		return (handle_cd_too_many_args());
	new_dir = ft_strdup(str[1]);
	return (handle_cd_new_dir(node, new_dir));
}

void	err_num_chdir(char *str) //#TODO erros with no permission
{
	if (errno == ENOENT)
	{
		print_error("minishell: cd: ");
		print_error(str);
		print_error(": No such file or directory\n");
	}
	else if (errno == EACCES)
	{
		print_error("minishell: cd: ");
		print_error(str);
		print_error(": permission denied\n");
	}
	else if (errno == ENOTDIR)
	{
		print_error("minishell: cd: ");
		print_error(str);
		print_error(": not a directory\n");
	}
	else
	{
		perror("minishell");
	}
}

void	update_old_pwd(t_pipes *node)
{
	char	*old_dir;
	char	*name;
	char	*str_array[3];
	char	*total;
	int		total_size;

	old_dir = getcwd(NULL, 0);
	if (!old_dir)
		return ;
	name = "OLDPWD=";
	total_size = ft_strlen(name) + ft_strlen(old_dir) + 1;
	total = malloc(total_size);
	ft_strlcpy(total, name, ft_strlen(name) + 1);
	ft_strlcat(total, old_dir, total_size);
	str_array[0] = NULL;
	str_array[1] = total;
	str_array[2] = NULL;
	ft_export(node, str_array);
	free(total);
	free(old_dir);
}

void	update_current_pwd(t_pipes *node)
{
	char	*old_dir;
	char	*name;
	char	*str_array[3];
	char	*total;
	int		total_size;

	old_dir = getcwd(NULL, 0);
	name = "PWD=";
	total_size = ft_strlen(name) + ft_strlen(old_dir) + 1;
	total = malloc(total_size);
	ft_strlcpy(total, name, ft_strlen(name) + 1);
	ft_strlcat(total, old_dir, total_size);
	str_array[0] = NULL;
	str_array[1] = total;
	str_array[2] = NULL;
	ft_export(node, str_array);
	free(total);
	free(old_dir);
}

int	cd_home(t_pipes *node, char **str)
{
	t_envs	*current;
	char	*new_dir;

	new_dir = NULL;
	current = node->init->envs;
	if (str[1] == NULL)
	{
		new_dir = ft_getenv(current, "HOME");
	}
	else if (!ft_strcmp(str[1], "") || !ft_strcmp(str[1], "~"))
		new_dir = getenv("HOME");
	if (new_dir != NULL)
	{
		chdir(new_dir);
		free(new_dir);
		update_current_pwd(node);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
