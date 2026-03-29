/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd_with_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:57:15 by hel-band          #+#    #+#             */
/*   Updated: 2024/10/06 14:55:22 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	char	*tmp;

	tmp = NULL;
	old = get_env_var_value(data->env, "PWD");
	if (!old)
	{
		tmp = getcwd(cwd, sizeof(cwd));
		if (tmp == NULL)
		{
			data->exit_status = 1;
			return ;
		}
		tmp = ft_strjoin("PWD=", tmp);
		ft_lstadd_back(&data->env, ft_lstnew_index(ft_strdup(tmp), 2));
		free (tmp);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		data->exit_status = 1;
		return ;
	}
	update_pwd_and_oldpwd(data, dir, old);
	data->exit_status = 0;
}

static void	navigate_to_directory(t_data *data, char *arg)
{
	struct stat	file_info;

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
}

static void	handle_failed_getcwd(t_data *data)
{
	t_list	*temp;
	char	*str;

	temp = data->env;
	while (temp)
	{
		if (ft_strncmp("PWD=", (char *)temp->content, 4) == 0)
		{
			str = (char *)temp->content;
			temp->content = ft_strjoin((char *)temp->content, "/..");
			free(str);
			break ;
		}
		temp = temp->next;
	}
}

void	handle_cd_directory(t_data *data, char *arg)
{
	char	cwd[1024];
	char	*dir;
	char	*error_message;

	data->exit_status = 0;
	navigate_to_directory(data, arg);
	if (data->exit_status == 1)
		return ;
	dir = getcwd(cwd, sizeof(cwd));
	if (!dir)
	{
		error_message = "cd: error retrieving current directory: "
			"getcwd: cannot access parent directories: "
			"No such file or directory";
		ft_putendl_fd(error_message, 2);
		handle_failed_getcwd(data);
		data->exit_status = 0;
		return ;
	}
	retrieve_and_update_env(data, dir);
}
