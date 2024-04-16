/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:21:27 by jorteixe          #+#    #+#             */
/*   Updated: 2024/03/26 11:34:25 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_env(t_envs *head)
{
	t_envs	*current;

	current = head;
	while (current != NULL)
	{
		if (current->value && current->has_equal)
			printf("%s=%s\n", current->name, current->value);
		if (!current->value && current->has_equal)
			printf("%s= \n", current->name);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

void	shlvl_change(char **env_var)
{
	int		number;
	int		i;
	char	**temp_arr;
	char	*new_str;

	number = 0;
	i = 0;
	if (ft_strnstr(*env_var, "SHLVL", 5))
	{
		temp_arr = ft_split(*env_var, '=');
		number = ft_atoi(temp_arr[1]);
		free(temp_arr[1]);
		number++;
		temp_arr[1] = ft_itoa(number);
		new_str = ft_strjoin(temp_arr[0], "=");
		new_str = ft_strjoin_free(new_str, temp_arr[1]);
		while (new_str[i])
		{
			(*env_var)[i] = new_str[i];
			i++;
		}
		(*env_var)[i] = '\0';
		free_args(temp_arr);
		free(new_str);
	}
}
