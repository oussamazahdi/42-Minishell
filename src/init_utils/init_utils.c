/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:00:54 by hel-band          #+#    #+#             */
/*   Updated: 2024/08/15 13:00:54 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_clear_env(t_data *data)
{
	if (data->env == NULL)
	{
		data->env = ft_empty_env();
		check_shlvl(data);
	}
}

void	copy_env(t_list **list, char **env, t_data *data)
{
	int	i;
	int	len;

	i = -1;
	len = ft_arrsize(env);
	while (env[++i] != NULL)
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
			ft_lstadd_back(list, ft_lstnew_index(ft_strdup("OLDPWD"), 1));
		else
		{
			if (len < 12 && ft_strncmp(env[i], "PATH=", 5) == 0)
				ft_lstadd_back(list, ft_lstnew_index(ft_strdup(env[i]), 2));
			else
				ft_lstadd_back(list, ft_lstnew_index(ft_strdup(env[i]), 1));
			if (ft_strncmp(env[i], "HOME=", 5) == 0)
			{
				data->home = ft_calloc(1, ft_strlen(&env[i][5]) + 1);
				ft_strlcpy(data->home, &env[i][5], ft_strlen(&env[i][5]) + 1);
			}
		}
	}
	check_shlvl(data);
	ft_clear_env(data);
}

t_list	*ft_lstnew_index(void *content, int index)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->index = index;
	new->next = NULL;
	return (new);
}

int	env_builtin(t_data *data, char **args)
{
	t_list	*temp;

	temp = data->env;
	if (ft_check_env(temp) == 1 || ft_arrsize(args) > 1)
	{
		printf("env: No such file or directory\n");
		data->exit_status = 127;
		return (EXIT_SUCCESS);
	}
	while (temp)
	{
		if (ft_strchr(temp->content, '=') && temp->index == 1)
			ft_putendl_fd(temp->content, STDOUT_FILENO);
		temp = temp->next;
	}
	data->exit_status = 0;
	return (EXIT_SUCCESS);
}
