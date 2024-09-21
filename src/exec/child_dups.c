/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_dups.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:59:57 by hel-band          #+#    #+#             */
/*   Updated: 2024/08/15 12:59:57 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#include "../../include/minishell.h"

static void	first_command(t_args *args);
static void	middle_command(t_args *args);
static void	last_command(t_args *args);

void	deal_with_pipes(t_data *data)
{
	if (data->process_count > 1)
	{
		if (data->args->index == data->process_count - 1)
			last_command(data->args);
		else if (data->args->index == 0)
			first_command(data->args);
		else
			middle_command(data->args);
	}
	close_pipes(data->args);
}

static void	first_command(t_args *args)
{
	dup2(args->pipis[1], 1);
}

static void	middle_command(t_args *args)
{
	if (args->index % 2 == 0)
	{
		dup2(args->pipes[0], 0);
		dup2(args->pipis[1], 1);
	}
	else
	{
		dup2(args->pipis[0], 0);
		dup2(args->pipes[1], 1);
	}
}

static void	last_command(t_args *args)
{
	if (args->index % 2 == 0)
		dup2(args->pipes[0], 0);
	else
		dup2(args->pipis[0], 0);
}
