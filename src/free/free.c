/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:00:47 by hel-band          #+#    #+#             */
/*   Updated: 2024/08/15 13:00:47 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_cmd_not_found(char **path, char **env, t_data *data, pid_t *pids)
{
	free(pids);
	ft_free_str_arr(&path);
	ft_free_str_arr(&env);
	free_exec(data->exec);
	free_for_all(data);
}

void	free_builtin(t_data *data, pid_t *pids)
{
	if (pids != NULL)
		free(pids);
	if (data->exec != NULL)
		free_exec(data->exec);
	free_for_all(data);
}

void	free_for_all(t_data	*data)
{
	rl_clear_history();
	if (data->env != NULL)
		free_list(data->env);
	if (data->lexer != NULL)
		free(data->lexer);
	if (data->home != NULL)
		free(data->home);
	if (data != NULL)
		free(data);
}

void	free_list(t_list *list)
{
	t_list	*temp;

	temp = list;
	while (temp != NULL)
	{
		list = list->next;
		if (temp->content)
			free(temp->content);
		free(temp);
		temp = list;
	}
}

void	free_exec(t_exec *exec)
{
	t_exec	*temp;

	temp = exec;
	if (!temp)
		return ;
	if (temp->cmd)
		ft_free_str_arr(&temp->cmd);
	free(exec);
}
