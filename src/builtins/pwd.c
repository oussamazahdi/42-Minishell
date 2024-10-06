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
	t_list	*temp;

	temp = data->env;
	dir = getcwd(cwd, sizeof(cwd));
	if (!dir)
	{
		while (temp)
		{
			if (ft_strncmp("PWD=", (char *)temp->content, 4) == 0)
			{
				dir = (char *)temp->content + 4;
				break ;
			}
			temp = temp->next;
		}
		data->exit_status = EXIT_FAILURE;
		printf("%s\n", dir);
		return (EXIT_FAILURE);
	}
	printf("%s\n", dir);
	data->exit_status = EXIT_SUCCESS;
	return (EXIT_SUCCESS);
}
