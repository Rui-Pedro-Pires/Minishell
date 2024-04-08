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

char    **listfiles(char *dirname, char *str_condition);

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

char	**ft_strjoin_files(char **s1, char **s2)
{
	char	**new_str;
	int		i;
	int		n;

    if (!s2)
        return (s1);
    new_str = ft_calloc(sizeof(char *), array_size(s1) + array_size(s2) + 1);
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

int check_equal_end(char *file, char *str_condition)
{
    int i;
    int x;

    i = ft_strlen(str_condition) - 1;
    x = ft_strlen(file) - 1;
    while (i > 0 && x >= 0)
    {
        if (str_condition[i] != file[x])
            return (1);
        i--;
        x--;
    }
    return (0);
}

int mega_compare(char *file, char *str_condition)
{
    if (ft_strcmp(str_condition, "*"))
        return (0);
    else if (!ft_strncmp(str_condition, "*", 1))
        return (check_equal_end(file, str_condition));
    else if (str_condition[ft_strlen(str_condition) - 1] == '*')
        return (ft_strncmp(str_condition, file, ft_strlen(str_condition) - 2));
    return (1);
}

char    **iterate_files(DIR *dirp, struct dirent *entity, char *str_condition)
{
    char            **files;

    files = NULL;
    while (entity)
    {
        if (strncmp(entity->d_name, ".", 1) && mega_compare(entity->d_name, str_condition) == 0)
            files = push(files, entity->d_name);
        entity = readdir(dirp);
    }
    return (files);
}

char    **listfiles(char *dirname, char *str_condition)
{
    DIR *dirp;
    struct dirent   *entity;
    char    **files;
    
    files = NULL;
    dirp = opendir(dirname);
    entity = readdir(dirp);
    if (dirp == NULL)
        return (NULL);
    files = iterate_files(dirp, entity, str_condition);
    closedir(dirp);
    return (files);
}
