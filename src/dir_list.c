/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:02:30 by ruiolive          #+#    #+#             */
/*   Updated: 2024/03/31 15:16:59 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    **listfiles(char *dirname, int recursive);

int     array_size(char **file)
{
    int i;

    i = 0;
    if (!file)
        return (0);
    while (file[i])
        i++;
    return (i);
}

char	*str_join_with_slash(char *s1, char *s2)
{
	char	*new_str;
	int		i;
	int		n;

	new_str = malloc(strlen(s1) + ft_strlen(s2) + 2);
	if (!new_str)
		return (NULL);
	i = 0;
	n = 0;
	while (s1[i] != '\0')
		new_str[n++] = s1[i++];
	i = 0;
	new_str[n++] = '/';
	while (s2[i] != '\0')
		new_str[n++] = s2[i++];
	new_str[n] = '\0';
	return (new_str);
}

char	**ft_strjoin_files(char **s1, char **s2)
{
	char	**new_str;
	int		i;
	int		n;

	new_str = ft_calloc(sizeof(char *), array_size(s1) + array_size(s2) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	n = 0;
	while (s1[i])
		new_str[n++] = ft_strdup(s1[i++]);
	i = 0;
	while (s2[i])
		new_str[n++] = ft_strdup(s2[i++]);
    free_args(s1);
    free_args(s2);
	return (new_str);
}

char    **push(char **files, char *str_to_add)
{
    char    **new_files;
    int size;
    int i;

    i = 0;
    if (!files)
    {
        new_files = ft_calloc(sizeof(char *), 2);
        new_files[0] = ft_strdup(str_to_add);
        free(str_to_add);
        return (new_files);
    }
    size = array_size(files);
    new_files = ft_calloc(sizeof(char *), size + 2);
    if (!new_files)
        return (NULL);
    while (files[i])
    {
        new_files[i] = ft_strdup(files[i]);
        i++;
    }
    new_files[i] = ft_strdup(str_to_add);
    free_args(files);
    free(str_to_add);
    return (new_files);
}

char    **iterate_files(DIR *dirp, struct dirent *entity, char *dirname, int recursive)
{
    char            **files;
    char            **recursive_files;
    char            *path;
    (void) dirname;

    files = NULL;
    recursive_files = NULL;
    while (entity)
    {
        if (strncmp(entity->d_name, ".", 1))
        {
            // path = str_join_with_slash(dirname, entity->d_name);
            path = ft_strdup(entity->d_name);
            files = push(files, path);
        }
        if (entity->d_type == 4 && ft_strncmp(entity->d_name, ".", 1) \
        && ft_strcmp(entity->d_name, ".") && ft_strcmp(entity->d_name, "..") && recursive == 0)
        {
            // path = str_join_with_slash(dirname, entity->d_name);
            path = ft_strdup(entity->d_name);
            recursive_files = listfiles(path, 1);
            files = ft_strjoin_files(files, recursive_files);
            free(path);
        }
        entity = readdir(dirp);
    }
    return (files);
}

char    **listfiles(char *dirname, int recursive)
{
    DIR *dirp;
    struct dirent   *entity;
    char    **files;
    
    files = NULL;
    dirp = opendir(dirname);
    entity = readdir(dirp);
    if (dirp == NULL)
        return (NULL);
    files = iterate_files(dirp, entity, dirname, recursive);
    closedir(dirp);
    return (files);
}
