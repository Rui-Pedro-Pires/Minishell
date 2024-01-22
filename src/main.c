/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:58:22 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/22 16:05:27 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **env)
{
    char    *input;
    t_data  *head;

    head = NULL;
    (void)env;
    (void)argv;
    (void)argc;
    while (1)
    {
        input = readline("");
        if (input && *input)
            add_history(input);
        check_unfinished_quotes(input);
        wrong_specialch_syntax(input);
        creat_list(&head, input);
        while (head)
        {
            printf("CMD: %s\n", head->cmd);
            printf("PIPE_TYPE: %d\n", head->pipe_type);
            head = head->next;
        }
        free(input);
    }
    rl_clear_history();
}
