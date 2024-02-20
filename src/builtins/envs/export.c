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

	str = str_array[1];
	if (str_array[2] != NULL)
		printf("\nruiolive&&jorteixe@minishell: cd: too many arguments\n");
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
		printf("Env already exists\n");
		printf("Name: %s\n", new_node->name);
		printf("Value: %s\n", new_node->value);
		free(new_node);
		return ;
	}
	current->next = new_node;
}

bool	export_is_valid(char *str)
{
	int	i;

	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (str[i] == '=' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
	{
		i++;
	}
	else
	{
		return (false);
	}
	while (ft_isalnum(str[i]) && (ft_isalnum(str[i]) || str[i] == '_'))
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
