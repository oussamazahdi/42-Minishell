/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd_with_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:57:15 by hel-band          #+#    #+#             */
/*   Updated: 2024/09/17 17:24:57 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static void	update_pwd_and_oldpwd(t_data *data, char *dir, char *old)
{
	t_list	*temp;
	int		flag;
	char	*str;

	flag = 0;
	temp = data->env;
	while (temp && old)
	{
		if (ft_strncmp("PWD=", (char *)temp->content, 4) == 0)
		{
			free(temp->content);
			temp->content = ft_strjoin("PWD=", dir);
			flag = 1;
		}
		else if (ft_strncmp("OLDPWD", (char *)temp->content, 6) == 0)
		{
			str = temp->content;
			temp->content = ft_strjoin("OLDPWD=", old);
			free(str);
		}
		temp = temp->next;
	}
	if (flag == 0)
		data->exit_status = 1;
}

static void	retrieve_and_update_env(t_data *data, char *dir)
{
	char	cwd[1024];
	char	*old;

	old = get_env_var_value(data->env, "PWD");
	if (!old)
	{
		data->exit_status = 1;
		return ;
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		data->exit_status = 1;
		return ;
	}
	update_pwd_and_oldpwd(data, dir, old);
	data->exit_status = 0;
}

void	handle_cd_directory(t_data *data, char *arg)
{
	struct stat	file_info;
	char		cwd[1024];
	char		*dir;

	if (stat(arg, &file_info) != 0)
	{
		ft_printf_fd(2, "cd: %s: No such file or directory\n", arg);
		data->exit_status = 1;
		return ;
	}
	if (chdir(arg) != 0)
	{
		perror("cd");
		data->exit_status = 1;
		return ;
	}
	dir = getcwd(cwd, sizeof(cwd));
	if (!dir)
	{
		ft_putendl_fd("cd: error retrieving current directory", 2);
		data->exit_status = 1;
		return ;
	}
	retrieve_and_update_env(data, dir);
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
