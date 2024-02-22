/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:30:17 by jorteixe          #+#    #+#             */
/*   Updated: 2024/02/16 14:30:17 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_export(t_envs *head, char **str_array)
{
	t_envs	*new_node;
	t_envs	*current;
	char	*str;

	if (str_array[1] == NULL)
	{
		ft_env(head);
		return ;
	}
	str = str_array[1];
	if (str_array[2] != NULL)
	{
		printf("\nruiolive&&jorteixe@minishell: export: too many arguments\n");
		return ;
	}
	if (!export_is_valid(str))
	{
		printf("Wrong Input: %s\n", str);
		return ;
	}
	new_node = create_env_node(str);
	current = head;
	while (current->next != NULL && !ft_strcmp(current->name, new_node->name))
		current = current->next;
	if (ft_strcmp(current->name, new_node->name))
	{
		free(current->value);
		current->value = ft_strdup(new_node->value);
		return ;
	}
	current->next = new_node;
}

bool	export_is_valid(char *str)
{
	int	i;

	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '/')
		i++;
	if (str[i] == '=' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_' || str[i
				+ 1] == '/'))
	{
		i++;
	}
	else
	{
		return (false);
	}
	while (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '/')
		i++;
	if (str[i] != '\0')
		return (false);
	return (true);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (str1[i] && str1[i] == str2[i])
		i++;
	if (str1[i] == '\0' && str2[i] == '\0')
		return (1);
	return (0);
}
