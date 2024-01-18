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

void    free_args(char **args)
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
        input = readline("");
        if (input && *input)
            add_history(input);
        args = ft_split(input, ' ');
        cmd = ft_strjoin(path, args[0]);
        if (ft_strncmp(args[0], "cd", 2) == 0)
            chdir(args[1]);
        pid = fork();
        if (pid == 0)
        {
            execve(cmd, args, NULL);
            return (0);
        }
        waitpid(pid, NULL, 0);
        free(input);
        free_args(args);
        free(cmd);

    }
    rl_clear_history();
}
fds