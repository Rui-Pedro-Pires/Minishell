/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heardoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:09:40 by jorteixe          #+#    #+#             */
/*   Updated: 2024/04/12 12:09:43 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*read_heardoc_buffer(int fd)
{
	char	*buffer;
	char	*new_str;

	buffer = ft_calloc(sizeof(char), 2);
	new_str = ft_strdup("");
	while (1)
	{
		if (read(fd, buffer, 1) <= 0)
			break ;
		new_str = ft_strjoin_free(new_str, buffer);
	}
	free(buffer);
	return (new_str);
}
