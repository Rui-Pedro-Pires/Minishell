/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:46:54 by jorteixe          #+#    #+#             */
/*   Updated: 2024/02/15 14:46:57 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	check_newline(char *str, bool *new_line);
bool	is_valid_no_new_line(char *str);
void	print_d_array_with_newline_control(char **str_array, bool new_line);
void	print_d_array_aux(char **str_array, int i);

int	ft_echo(char **str_array)
{
	bool	new_line;
	int		i;

	new_line = false;
	i = 1;
	if (!str_array[i])
	{
		printf("\n");
		return (EXIT_SUCCESS);
	}
	check_newline(str_array[1], &new_line);
	if (str_array[2] == NULL && new_line == false)
		return (EXIT_SUCCESS);
	print_d_array_with_newline_control(str_array, new_line);
	return (EXIT_SUCCESS);
}

void	check_newline(char *str, bool *new_line)
{
	if (is_valid_no_new_line(str))
		*new_line = false;
	else
		*new_line = true;
}

bool	is_valid_no_new_line(char *str)
{
	int	i;

	i = 0;
	if (!ft_strcmp(str, "-n"))
		return (true);
	else if (str[i] == '-' && str[i + 1] == 'n')
	{
		i++;
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (true);
	}
	return (false);
}

void	print_d_array_with_newline_control(char **str_array, bool new_line)
{
	int	i;

	i = 1;
	if (new_line == true)
	{
		print_d_array_aux(str_array, i);
		printf("\n");
	}
	else
	{
		while (is_valid_no_new_line(str_array[i]))
			i++;
		print_d_array_aux(str_array, i);
	}
}

void	print_d_array_aux(char **str_array, int i)
{
	while (str_array[i + 1] != NULL)
	{
		printf("%s ", str_array[i]);
		i++;
	}
	if (str_array[i])
		printf("%s", str_array[i]);
}
