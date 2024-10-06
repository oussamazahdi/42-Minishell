/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_all_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:00:35 by hel-band          #+#    #+#             */
/*   Updated: 2024/08/15 13:00:35 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_process_status(t_data *data, int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
		{
			data->exit_status = 131;
		}
		else if (WTERMSIG(status) == 2)
		{
			data->exit_status = 130;
		}
	}
	else if (WIFEXITED(status) && data->exit_status != 1)
	{
		data->exit_status = WEXITSTATUS(status);
	}
}

void	wait_all_processes(t_data *data, pid_t *pids, int flag)
{
	int	i;
	int	status;

	i = -1;
	if (flag == 1)
	{
		waitpid(pids[++i], &status, 0);
		handle_process_status(data, status);
	}
	else
	{
		while (++i < data->process_count)
		{
			waitpid(pids[i], &status, 0);
			handle_process_status(data, status);
		}
	}
	if (data->exit_status == 131)
		write (1, "Quit: 3\n", 8);
	if (data->exit_status == 130)
	{
		write(1, "\n", 1);
	}
}
