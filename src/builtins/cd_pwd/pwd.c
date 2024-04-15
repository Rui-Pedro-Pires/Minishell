/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:22:23 by jorteixe          #+#    #+#             */
/*   Updated: 2024/02/14 15:22:23 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_pwd(t_pipes *node) //#TODO Return EXIT_FAILURE or EXIT_SUCCESS
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		pwd = ft_getenv(node->init->envs, "PWD");
		if (!pwd)
		{
			perror("minishell");
			return (EXIT_FAILURE);
		}
	}
	printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
