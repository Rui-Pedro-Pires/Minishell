/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive  <ruiolive@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:58:22 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/18 12:01:38 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
    char *input;
    char    *cmd;
    char    *path;
    char    **args;
    int pid;

    path = "/usr/bin/";
    while (1)
    {
        pid = fork();
        if (pid == 0)
        {
            input = readline("");
            if (input && *input)
                add_history(input);
            args = ft_split(input, ' ');
            cmd = ft_strjoin(path, args[0]);
            execve(cmd, args, NULL);
            free(input);
            return (0);
        }
    }
    rl_clear_history();
}