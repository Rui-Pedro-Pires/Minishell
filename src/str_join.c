/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive  <ruiolive@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:33:17 by ruiolive          #+#    #+#             */
/*   Updated: 2024/02/08 09:33:17 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*str_join_with_space(char *s1, char *s2)
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

char	*str_join_with_newline(char *s1, char *s2)
{
	char	*new_str;
	int		i;
	int		n;
	int		size;

	if (!s1 || !(*s1))
		size = ft_strlen(s2);
	else
		size = ft_strlen(s1) + ft_strlen(s2);
	new_str = malloc(size + 2);
	if (!new_str)
		return (NULL);
	i = 0;
	n = 0;
	while (s1[i] != '\0' && s1)
		new_str[n++] = s1[i++];
	i = 0;
	new_str[n++] = '\n';
	while (s2[i] != '\0' && s2)
		new_str[n++] = s2[i++];
	new_str[n] = '\0';
	free(s1);
	free(s2);
	return (new_str);
}

char	*add_nl(char *s1, char *s2)
{
	char	*new_str;
	int		i;
	int		n;
	int		size;

	if (!s1 || !(*s1))
		size = ft_strlen(s2);
	else
		size = ft_strlen(s1) + ft_strlen(s2);
	new_str = malloc(size + 2);
	if (!new_str)
		return (NULL);
	i = 0;
	n = 0;
	while (s1[i] != '\0' && s1)
		new_str[n++] = s1[i++];
	i = 0;
	while (s2[i] != '\0' && s2)
		new_str[n++] = s2[i++];
	new_str[n] = '\0';
	free(s1);
	return (new_str);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new_str;
	int		i;
	int		n;

	new_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	n = 0;
	while (s1[i] != '\0')
	{
		new_str[n] = s1[i];
		i++;
		n++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		new_str[n] = s2[i];
		i++;
		n++;
	}
	new_str[n] = '\0';
	free(s1);
	return (new_str);
}

char	*ft_strjoin_free_v2(char *s1, char *s2)
{
	char	*new_str;
	int		i;
	int		n;

	new_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	n = 0;
	while (s1[i] != '\0')
	{
		new_str[n] = s1[i];
		i++;
		n++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		new_str[n] = s2[i];
		i++;
		n++;
	}
	new_str[n] = '\0';
	free(s2);
	return (new_str);
}
