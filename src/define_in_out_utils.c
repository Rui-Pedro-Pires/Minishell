/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_in_out_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive  <ruiolive@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 20:17:32 by ruiolive          #+#    #+#             */
/*   Updated: 2024/02/29 20:17:32 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*search_file_name(char *str)
{
	int		i;
	int		x;
	char	*file_name;
	i = 1;
	while (str[i] && str[i] == ' ')
		i++;
	x = i;
	while (str[x] && !ft_strchr("<> ", str[i]))
		x++;
	file_name = malloc(sizeof(char) * x - i + 1);
	x = 0;
	while (str[i] && !ft_strchr("<> ", str[i]))
	{
		file_name[x] = str[i];
		x++;
		i++;
	}
	file_name[x] = '\0';
	return (file_name);
}
