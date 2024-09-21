/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:46:52 by ozahdi            #+#    #+#             */
/*   Updated: 2024/09/19 10:45:07 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exit(char *read, t_data **line)
{
	if (read && ft_strlen(read) == 0)
	{
		free(read);
		read = NULL;
		(*line)->exit_status = 0;
		return (0);
	}
	if (ft_strlen(read) > 0)
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
