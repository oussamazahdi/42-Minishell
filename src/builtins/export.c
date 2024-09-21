/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:59:28 by hel-band          #+#    #+#             */
/*   Updated: 2024/08/15 12:59:28 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	update_existing_key(t_list *temp, char **arr, t_data *data,
				char *key)
{
	char	*new_content;

	if (arr[1])
	{
		if (!ft_strchr(temp->content, '='))
			temp->content = ft_strjoin(temp->content, "=");
		new_content = ft_strjoin(temp->content, arr[1]);
		if (new_content)
		{
			free(temp->content);
			temp->content = new_content;
		}
		else
		{
			data->exit_status = 1;
			return (0);
		}
	}
	else if (ft_strchr(data->var, '=') && !ft_strchr(data->var, '+'))
	{
		free(temp->content);
		temp->content = ft_strdup(ft_strjoin(key, "="));
	}
	return (1);
}

static int	append_or_update_key(t_list *temp, char **arr, t_data *data)
{
	char	**env;
	int		found;
	char	*key;

	found = 0;
	key = remove_plus(arr[0]);
	if (!key)
	{
		data->exit_status = 1;
		return (0);
	}
	while (temp)
	{
		env = ft_split(temp->content, '=');
		if (env[0] && ft_strncmp(env[0], key, ft_strlen(key)) == 0)
		{
			found = update_existing_key(temp, arr, data, key);
			break ;
		}
		ft_free_str_arr(&env);
		temp = temp->next;
	}
	if (env && *env)
		ft_free_str_arr(&env);
	return (free(key), found);
}

static int	process_key_update(t_list *temp, char **arr, char *var,
				t_data *data)
{
	char	*new_content;

	if (arr[1])
	{
		if (!ft_strchr(temp->content, '='))
			temp->content = ft_strjoin(temp->content, "=");
		new_content = ft_strdup(var);
		if (new_content)
		{
			free(temp->content);
			temp->content = new_content;
		}
		else
		{
			data->exit_status = 1;
			return (0);
		}
	}
	else if (ft_strchr(var, '='))
	{
		free(temp->content);
		temp->content = ft_strdup(var);
	}
	return (1);
}

static int	update_key(t_list *temp, char **arr, char *var, t_data *data)
{
	char	**env;
	int		found;

	found = 0;
	while (temp)
	{
		env = ft_split(temp->content, '=');
		if (env[0] && ft_strncmp(env[0], arr[0], ft_strlen(arr[0])) == 0)
		{
			found = 1;
			if (!process_key_update(temp, arr, var, data))
			{
				ft_free_str_arr(&env);
				env = NULL;
				return (0);
			}
			break ;
		}
		if (env)
			ft_free_str_arr(&env);
		temp = temp->next;
	}
	if (env && *env)
		ft_free_str_arr(&env);
	return (found);
}

int	search_key(t_list *temp, char **arr, char *var, t_data *data)
{
	if (ft_strchr(arr[0], '+'))
		return (append_or_update_key(temp, arr, data));
	else
		return (update_key(temp, arr, var, data));
}
