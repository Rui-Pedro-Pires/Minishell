/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:58:22 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/19 12:53:21 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
    char    *input;

    input = readline("");
    // check for more then allowed special caracters
    // wrong_specialch_syntax(input);
	char **splited = ft_split(input, ' ');
	int	i = 0;
	while (splited[i])
	{
		printf("%s\n", splited[i]);
		i++;
	}
    free(input);
    return (0);
}
