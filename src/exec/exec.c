/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:00:06 by hel-band          #+#    #+#             */
/*   Updated: 2024/08/15 13:00:06 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	commands_fork(t_args *args, t_data *data);
static void	execute_builtin_parent_process(t_data *data);
static void	execute_child_process(t_data *data, t_args *args);
static void	child_proc_utils(t_data *data, t_list *temp, int *lex, pid_t *pids);

void	execute(t_data **data)
{
	t_args	args;

	signal(SIGINT, ft_handler);
	signal(SIGQUIT, ft_handler1);
	(*data)->args = &args;
	args.index = 0;
	pipe(args.pipis);
	pipe(args.pipes);
	commands_fork(&args, *data);
	unlink("/tmp/herdoc.txt");
	close_pipes(&args);
}

static void	commands_fork(t_args *args, t_data *data)
{
	data->has_cmd = 0;
	data->has_builtin = 0;
	if (data->process_count == 1 && data->builtin_check == 1)
		execute_builtin_parent_process(data);
	else
		execute_child_process(data, args);
	// printf("exit_status = %d\n", data->exit_status);
}

static void	execute_builtin_parent_process(t_data *data)
{
	int	fd[2];
	int	result;
	int	backup[2];

	backup[0] = dup(0);
	backup[1] = dup(1);
	result = validate_files(data->token, data->lexer, &fd[0], &fd[1]);
	if (result == 1)
	{
		get_cmd_and_args(data->token, data->lexer, data);
		if (fd[0] != -2 || fd[1] != -2)
			redirect_files(fd[0], fd[1]);
		execute_builtin(data, data->exec, NULL);
		free_exec(data->exec);
	}
	else if (result == 2 || result == 4)
		data->exit_status = 1;
	else if (result == 3)
		data->exit_status = 126;
	dup2(backup[0], 0);
	dup2(backup[1], 1);
	close_files(backup[0], backup[1]);
	close_files(fd[0], fd[1]);
}

static void	execute_child_process(t_data *data, t_args *args)
{
	pid_t	*pids;
	int		i;
	t_list	*temp;

	i = 0;
	temp = data->token;
	pids = ft_calloc(sizeof(int), data->process_count);
	while (args->index < data->process_count)
	{
		if (data->lexer[i] == PIPE)
		{
			i++;
			temp = temp->next;
		}
		pids[data->args->index] = fork();
		if (pids[data->args->index] == -1)
		{
			perror("fork");
			data->exit_status = 1;
			break ;
		}
		child_proc_utils(data, temp, &data->lexer[i], pids);
		while (temp != NULL && data->lexer[i] != PIPE)
		{
			temp = temp->next;
			i++;
		}
		args->index++;
	}
	wait_all_processes(data, pids, data->process_count);
	free(pids);
}

static void	child_proc_utils(t_data *data, t_list *temp, int *lex, pid_t *pids)
{
	if (pids[data->args->index] == 0)
	{
		child_process(data, temp, lex, pids);
	}
	recycle_pipe(data->args);
}
