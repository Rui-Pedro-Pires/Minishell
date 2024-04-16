/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:30:17 by jorteixe          #+#    #+#             */
/*   Updated: 2024/03/26 11:40:04 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void		add_env(t_envs *head, char *str);
static int	print_export_list(t_envs *head);
int			ft_is_only_digit(char *str);

int	ft_export(t_pipes *node, char **str_array)
{
	t_envs	*current;
	t_envs	*current_sorted;
	int		i;
	int		status;

	current = node->init->envs;
	current_sorted = bubble_sort(node->init->sorted_envs);
	if (str_array[1] == NULL)
		return (print_export_list(current_sorted));
	i = 0;
	status = 0;
	while (str_array[++i])
	{
		if (!export_is_valid(str_array[i]))
		{
			print_error("minishell: export: `");
			print_error(str_array[i]);
			print_error("': not a valid identifier\n");
			status = 1;
			continue ;
		}
		add_env(current, str_array[i]);
		add_env(current_sorted, str_array[i]);
	}
	return (status);
}

bool	export_is_valid(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '=' || ft_is_only_digit(str) == 1)
		return (false);
	while (ft_isalnum(str[i]))
		i++;
	if (!str[i] || str[i] == '=')
		return (true);
	if (!ft_isalnum(str[i]))
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
		return (0);
	return (str1[i] - str2[i]);
}

void	add_env(t_envs *head, char *str)
{
	t_envs	*current;
	t_envs	*new_node;

	current = head;
	new_node = create_env_node(str, false);
	if (!current)
		return ;
	while (current->next != NULL && ft_strcmp(current->name, new_node->name))
		current = current->next;
	if (!ft_strcmp(current->name, new_node->name))
	{
		free(current->value);
		free(current->name);
		free(current->whole_str);
		current->value = ft_strdup(new_node->value);
		current->name = ft_strdup(new_node->name);
		current->whole_str = ft_strdup(new_node->whole_str);
		current->has_equal = true;
		free(new_node->value);
		free(new_node->name);
		free(new_node->whole_str);
		free(new_node);
		return ;
	}
	current->next = new_node;
}

static int	print_export_list(t_envs *head)
{
	t_envs	*current;

	current = head;
	while (current != NULL)
	{
		printf("declare -x %s", current->name);
		if (current->value && current->has_equal)
			printf("=\"%s\"\n", current->value);
		else if (!current->value && current->has_equal)
			printf("=\"\"\n");
		else
			printf("\n");
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
