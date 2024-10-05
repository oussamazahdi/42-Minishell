/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:00:01 by hel-band          #+#    #+#             */
/*   Updated: 2024/08/15 13:00:01 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	child_process(t_data *data, t_list *token, int *lexer, pid_t *pids)
{
	int	fd[2];
	int	result;

	result = validate_files(token, lexer, &fd[0], &fd[1]);
	if (result == 1)
	{
		get_cmd_and_args(token, lexer, data);
		deal_with_pipes(data);
		if (fd[0] != -2 || fd[1] != -2)
			redirect_files(fd[0], fd[1]);
		if (data->has_builtin == 1 || data->has_cmd == 1)
		{
			data->exit_status = 0;
			finally_execute(data, fd, pids);
		}
	}
	else if (result == 2 || result == 4)
		data->exit_status = 1;
	else if (result == 3)
		data->exit_status = 126;
	close_files(fd[0], fd[1]);
	free(pids);
	free_for_all(data);
	exit(data->exit_status);
}

void	update_last_command(t_data *data, char *command)
{
	t_list	*temp;
	char	*new_value;
	char	*old;

	temp = data->env;
	if (ft_strnstr(command, "/usr/bin/", ft_strlen(command)) != NULL)
		new_value = ft_strjoin("_=", command);
	else
		new_value = ft_strjoin("_=/usr/bin/", command);
	if (!new_value)
		return ;
	while (temp)
	{
		if (ft_strlen(temp->content) != 0
			&& ft_strncmp("_=", (char *)temp->content, 2) == 0)
		{
			old = temp->content;
			temp->content = new_value;
			free(old);
			break ;
		}
		temp = temp->next;
	}
	if (!temp)
		ft_lstadd_back(&data->env, ft_lstnew(new_value));
}

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
