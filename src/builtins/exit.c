/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:24:53 by hel-band          #+#    #+#             */
/*   Updated: 2024/09/20 11:04:56 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_print_free(t_data *data, pid_t *pids)
{
	ft_printf_fd(2, "exit: numeric argument required\n");
	free_builtin(data, pids);
	exit(255);
}

void	exit_builtin(t_data *data, pid_t *pids, char **args)
{
	long	num;
	int		exit_code;
	bool	error;

	if (!is_quiet_mode(data))
		ft_putendl_fd("exit", 2);
	num = data->exit_status;
	error = false;
	if (!args || !args[1])
		exit_code = 0;
	else
	{
		exit_code = get_exit_code(args[1], &error);
		if (error)
			ft_print_free(data, pids);
		else if (args[2])
		{
			ft_printf_fd(2, "exit: too many arguments\n");
			data->exit_status = 1;
			return ;
		}
	}
	free_builtin(data, pids);
	exit(exit_code);
}
