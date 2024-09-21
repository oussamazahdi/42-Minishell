/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:59:37 by hel-band          #+#    #+#             */
/*   Updated: 2024/08/15 12:59:37 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd_builtin(t_data *data)
{
	char	cwd[1024];
	char	*dir;

	dir = getcwd(cwd, sizeof(cwd));
	if (!dir)
	{
		perror("minishell: pwd: ");
		data->exit_status = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	printf("%s\n", dir);
	data->exit_status = EXIT_SUCCESS;
	return (EXIT_SUCCESS);
}
