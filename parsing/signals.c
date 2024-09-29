/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:46:52 by ozahdi            #+#    #+#             */
/*   Updated: 2024/09/29 16:40:53 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exit(char *read, t_data **line)
{
	if (g_herdoc == 1)
	{
		(*line)->exit_status = 1;
		g_herdoc = 0;
		if (!read)
		{
			printf("exit\n");
			exit((*line)->exit_status);
		}
		if (read && ft_strlen(read) == 0)
			return (free(read), 0);
	}
	if (read && ft_strlen(read) == 0)
		return (free(read), (*line)->exit_status = 0, 0);
	if (read && ft_strlen(read) > 0)
		add_history(read);
	if (!read)
	{
		rl_clear_history();
		printf("exit\n");
		exit((*line)->exit_status);
	}
	return (1);
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		g_herdoc = 1;
		rl_redisplay();
	}
}

void	ft_handler1(int sig)
{
	(void)sig;
	write(1, "", 1);
}

void	ft_handler(int sig)
{
	(void)sig;
	write(1, "", 1);
}
