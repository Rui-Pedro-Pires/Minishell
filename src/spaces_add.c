/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:15:28 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/22 11:52:38 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	quotes_check(char *input, char c);
static  int count_special_chars(char *input);

char    *add_spaces(char *input)
{
    char *str;
    int i;
    int x;
    
    i = 0;
    x = 0;
    str = malloc(sizeof(char) * (ft_strlen(input) + count_special_chars(input) + 1));
    if (!str)
        return (NULL);
    while (input[i])
    {
        if (input[i] == 34)
			i += quotes_check(input + i, 34);
		else if (input[i] == 39)
			i += quotes_check(input + i, 39);
        else if ((input[i] == '|' && input[i + 1] == '|') || \
        (input[i] == '&' && input[i + 1] == '&') || \
        (input[i] == '<' && input[i + 1] == '<') || \
        (input[i] == '>' && input[i + 1] == '>'))
        {
            str[x++] = ' ';
            str[x++] = input[i++];
            str[x++] = input[i++];
            str[x++] = ' ';
        }
        else if (input[i] == '|' || input[i] == '&' || input[i] == '<' || input[i] == '>')
        {
            str[x++] = ' ';
            str[x++] = input[i++];
            str[x++] = ' ';
        }
        else
            str[x++] = input[i++];
    }
    str[x] = '\0';
    free(input);
    return (str);
}

static int	quotes_check(char *input, char c)
{
	int	i;

	i = 1;
	while (input[i] && input[i] != c)	
		i++;
	return (i + 1);
}

static  int count_special_chars(char *input)
{
    int i;
    int count;

    count = 0;
    i = 0;
    while (input[i])
    {
        if ((input[i] == '|' && input[i + 1] == '|') || \
        (input[i] == '&' && input[i + 1] == '&') || \
        (input[i] == '<' && input[i + 1] == '<') || \
        (input[i] == '>' && input[i + 1] == '>'))
        {
            count++;
            i += 2;
        }
        else if (input[i] == '|' || input[i] == '&' || input[i] == '<' || input[i] == '>')
        {
            count++;
            i++;
        }
        else
            i++;
    }
    return (count);
}
