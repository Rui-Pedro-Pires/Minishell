/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 19:54:41 by ruiolive          #+#    #+#             */
/*   Updated: 2024/04/06 12:04:04 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sigint(int sig)
{	
    if (sig == SIGINT)
    {
        rl_replace_line("", 0);
        printf("\n");
        rl_on_new_line();
        rl_redisplay();
        global_return_value = 130;
    }
}

void	update_status_sigint(int sig)
{
	if (sig == SIGINT)
        global_return_value = 130;
}

void	update_status_sigquit(int sig)
{
	if (sig == SIGQUIT)
        global_return_value = 131;
}
