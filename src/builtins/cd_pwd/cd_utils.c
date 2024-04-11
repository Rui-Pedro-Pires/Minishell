/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:41:21 by jorteixe          #+#    #+#             */
/*   Updated: 2024/04/11 11:41:21 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	handle_cd_home(t_pipes *node, char **str)
{
	if (cd_home(node, str) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else
	{
		print_error("minishell: cd: HOME not set\n");
		return (EXIT_FAILURE);
	}
}

int	handle_cd_too_many_args(void)
{
	print_error("bash: cd: too many arguments\n");
	return (EXIT_FAILURE);
}

int	handle_cd_new_dir(t_pipes *node, char *new_dir)
{
	if (chdir(new_dir) == (-1))
	{
		err_num_chdir(new_dir);
		free(new_dir);
		update_current_pwd(node);
		return (EXIT_FAILURE);
	}
	update_current_pwd(node);
	free(new_dir);
	return (EXIT_SUCCESS);
}
