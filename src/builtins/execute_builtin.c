/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:58:16 by hel-band          #+#    #+#             */
/*   Updated: 2024/08/15 12:58:16 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_builtin(t_data *data, t_exec *exec, pid_t *pids)
{
	if (ft_strcmp(data->exec->cmd[0], "env") == 0)
		env_builtin(data, exec->cmd);
	else if (ft_strcmp(data->exec->cmd[0], "pwd") == 0)
		pwd_builtin(data);
	else if (ft_strcmp(data->exec->cmd[0], "export") == 0)
		export_builtin(data, exec->cmd);
	else if (ft_strcmp(data->exec->cmd[0], "unset") == 0)
		unset_builtin(data, exec->cmd);
	else if (ft_strcmp(data->exec->cmd[0], "exit") == 0)
		exit_builtin(data, pids, exec->cmd);
	else if (ft_strcmp(data->exec->cmd[0], "echo") == 0)
		echo_builtin(data, exec->cmd);
	else if (ft_strcmp(data->exec->cmd[0], "cd") == 0)
		cd_builtin(data, exec->cmd);
	ft_add_enver(data);
}

void	export_builtin(t_data *data, char **args)
{
	t_list	*export;
	int		len;
	int		i;

	export = NULL;
	i = 0;
	len = ft_arrsize(args);
	if (len == 1)
		sort_env(copy_env_list(data->env, export));
	else
	{
		while (++i < len)
		{
			if (find_in_env(data, args[i]) == 0)
			{
				if (ft_strchr(args[i], '+'))
					args[i] = remove_plus(args[i]);
				ft_lstadd_back(&data->env,
					ft_lstnew_index(ft_strdup(args[i]), 1));
				data->exit_status = 0;
			}
		}
	}
}
