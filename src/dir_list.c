/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:02:30 by ruiolive          #+#    #+#             */
/*   Updated: 2024/04/02 11:46:22 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    **listfiles(char *dirname, int recursive, char *str_condition);

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
    return (new_files);
}

int mega_compare(char *file, char *str_condition)
{
    (void)file;
    (void)str_condition;
    return (0);
}

char    **iterate_files(DIR *dirp, struct dirent *entity, int recursive, char *str_condition)
{
    char            **files;
    char            **recursive_files;

    files = NULL;
    recursive_files = NULL;
    while (entity)
    {
        if (strncmp(entity->d_name, ".", 1))
            files = push(files, entity->d_name);
        if (entity->d_type == 4 && ft_strncmp(entity->d_name, ".", 1) \
        && ft_strcmp(entity->d_name, ".") && ft_strcmp(entity->d_name, "..") \
        && recursive == 0 && mega_compare(entity->d_name, str_condition) == 0)
        {
            recursive_files = listfiles(entity->d_name, 1, str_condition);
            files = ft_strjoin_files(files, recursive_files);
        }
        entity = readdir(dirp);
    }
    return (files);
}

char    **listfiles(char *dirname, int recursive, char *str_condition)
{
    DIR *dirp;
    struct dirent   *entity;
    char    **files;
    
    files = NULL;
    dirp = opendir(dirname);
    entity = readdir(dirp);
    if (dirp == NULL)
        return (NULL);
    files = iterate_files(dirp, entity, recursive, str_condition);
    closedir(dirp);
    return (files);
}
