/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:57:46 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/22 14:58:02 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    free_memory(char **args)
{
    int i;
    
    i = 0;
    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
}