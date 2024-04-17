/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:02:30 by ruiolive          #+#    #+#             */
/*   Updated: 2024/04/02 17:10:03 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	array_size(char **file)
{
	int	i;

	i = 0;
	if (!file)
		return (0);
	while (file[i])
		i++;
	return (i);
}

char	*iterate_files(DIR *dirp, struct dirent *entity)
{
	char	*files;

	files = NULL;
	while (entity)
	{
		if (ft_strncmp(entity->d_name, ".", 1) && ft_strncmp(entity->d_name,
				"..", 2))
		{
			if (!files)
				files = ft_strdup(entity->d_name);
			else
				files = str_join_with_space(files, entity->d_name, 1);
		}
		entity = readdir(dirp);
	}
	return (files);
}

char	*listfiles(char *dirname)
{
	DIR				*dirp;
	struct dirent	*entity;
	char			*files;

	files = NULL;
	dirp = opendir(dirname);
	if (dirp == NULL)
		return (NULL);
	entity = readdir(dirp);
	files = iterate_files(dirp, entity);
	closedir(dirp);
	return (files);
}
