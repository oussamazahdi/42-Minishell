/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:56:07 by hel-band          #+#    #+#             */
/*   Updated: 2024/08/15 15:56:07 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cd_builtin(t_data *data, char **args)
{
	int	len;

	len = ft_arrsize(args);
	if (len == 1)
		handle_cd_home(data);
	else if (len == 2)
		handle_cd_with_args(data, args[1]);
	data->env_flags = 0;
}

static int	change_directory_and_handle_error(t_data *data)
{
	if (chdir(data->home) != 0)
	{
		perror("cd");
		data->exit_status = 1;
		return (1);
	}
	return (0);
}

void	handle_cd_home(t_data *data)
{
	t_list	*temp;
	char	*old;
	char	*str;

	temp = data->env;
	old = get_env_var_value(data->env, "PWD");
	if (change_directory_and_handle_error(data) == 0)
	{
		while (temp)
		{
			if (ft_strncmp("PWD=", (char *)temp->content, 4) == 0)
			{
				free(temp->content);
				temp->content = ft_strjoin("PWD=", data->home);
			}
			else if (old && ft_strncmp("OLDPWD", (char *)temp->content, 6) == 0)
			{
				str = temp->content;
				temp->content = ft_strjoin("OLDPWD=", old);
				free (str);
			}
			temp = temp->next;
		}
		data->exit_status = 0;
	}
}

void	handle_cd_dash(t_data *data)
{
	char	*path;
	char	*old;

	path = get_env_var_value(data->env, "OLDPWD");
	old = get_env_var_value(data->env, "PWD");
	if (path == NULL || path[0] != '/')
	{
		ft_putendl_fd("cd: OLDPWD not set", 2);
		data->exit_status = 1;
		return ;
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		data->exit_status = 1;
		return ;
	}
	update_env_var(data->env, "PWD=", path, data);
	update_env_var(data->env, "OLDPWD=", old, data);
	if (data->exit_status != 1)
	{
		printf("%s\n", path);
		data->exit_status = 0;
	}
}

void	handle_cd_with_args(t_data *data, char *arg)
{
	if (ft_strncmp(arg, "-", 2) == 0)
		handle_cd_dash(data);
	else if (ft_strncmp(arg, "--", 3) == 0)
	{
		handle_cd_home(data);
		data->exit_status = 0;
	}
	else if (ft_strncmp(arg, "~", 2) == 0)
		handle_cd_home(data);
	else
		handle_cd_directory(data, arg);
}
