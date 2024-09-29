/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:00:29 by hel-band          #+#    #+#             */
/*   Updated: 2024/08/15 13:00:29 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	verify(int result, char *str, char **cmd, char **env)
{
	if (result == 0)
	{
		verify_permission(str, cmd, env);
		return (0);
	}
	return (-1);
}

static void	exit_with_error(t_data *data, pid_t *pids, int exit_code, int flag)
{
	if (flag == 1)
		ft_printf_fd(2, "%s: command not found\n", data->exec->cmd[0]);
	free_exec(data->exec);
	free(pids);
	free_for_all(data);
	exit(exit_code);
}

static void	handle_command_execution(t_data *data, int fd[], pid_t *pids)
{
	char	**env;
	char	**path;
	int		result;

	if (ft_strlen(data->exec->cmd[0]) == 0 && data->process_count == 1)
		exit_with_error(data, pids, 127, 1);
	else if (ft_strlen(data->exec->cmd[0]) == 0 && data->process_count > 1)
		exit_with_error(data, pids, 0, 0);
	env = turn_env_to_arr(data->env);
	path = find_path(env);
	result = try_paths(data->exec, path, env);
	close_files(fd[0], fd[1]);
	if (opendir(data->exec->cmd[0]))
		ft_printf_fd(2, "%s: is a directory\n", data->exec->cmd[0]);
	else if (ft_strchr(data->exec->cmd[0], '/')
		&& access(data->exec->cmd[0], F_OK))
		ft_printf_fd(2, "%s: No such file or directory\n", data->exec->cmd[0]);
	else if (result == 127)
		ft_printf_fd(2, "%s: command not found\n", data->exec->cmd[0]);
	else
		ft_printf_fd(2, "%s: permission denied\n", data->exec->cmd[0]);
	free_cmd_not_found(path, env, data, pids);
	exit(result);
}

static void	handle_builtin_execution(t_data *data, int fd[], pid_t *pids)
{
	int		ext_code;

	execute_builtin(data, data->exec, pids);
	close_files(fd[0], fd[1]);
	ext_code = data->exit_status;
	free_builtin(data, pids);
	exit(ext_code);
}

void	finally_execute(t_data *data, int fd[], pid_t *pids)
{
	if (data->exec->lex == CMD)
		handle_command_execution(data, fd, pids);
	else
		handle_builtin_execution(data, fd, pids);
}
