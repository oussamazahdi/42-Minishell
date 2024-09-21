/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:48:05 by hel-band          #+#    #+#             */
/*   Updated: 2024/09/17 12:05:43 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	append_equal_sign_if_missing(t_list *current)
{
	char	*new_content;

	if (current->content
		&& ft_strchr((char *)current->content, '=') == NULL)
	{
		new_content = ft_strjoin(current->content, "=");
		if (new_content)
		{
			free(current->content);
			current->content = new_content;
		}
	}
}

static char	*compare_and_get_value(t_list *current, char *tmp)
{
	char	*value;

	if (current->content
		&&ft_strncmp(tmp, (char *)current->content, ft_strlen(tmp)) == 0)
	{
		value = ft_strchr((char *)current->content, '=');
		if (value)
			return (value + 1);
	}
	return (NULL);
}

char	*get_env_var_value(t_list *env, char *var)
{
	t_list	*current;
	char	*tmp;
	char	*value;

	if (!env || !var)
		return (NULL);
	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (NULL);
	current = env;
	while (current)
	{
		append_equal_sign_if_missing(current);
		value = compare_and_get_value(current, tmp);
		if (value)
		{
			free(tmp);
			return (value);
		}
		current = current->next;
	}
	free(tmp);
	return (NULL);
}

void	update_env_var(t_list *env, char *prefix,
				char *new_value, t_data *data)
{
	t_list	*temp;
	char	*new_content;
	int		prefix_len;

	prefix_len = ft_strlen(prefix);
	temp = env;
	while (temp)
	{
		if (ft_strncmp(prefix, (char *)temp->content, prefix_len) == 0)
		{
			new_content = ft_strjoin(prefix, new_value);
			if (!new_content)
			{
				perror("ft_strjoin");
				data->exit_status = 1;
				return ;
			}
			temp->content = new_content;
			return ;
		}
		temp = temp->next;
	}
}

void	cd_dash_update_env_vars(t_data *data, char *path, char *old)
{
	update_env_var(data->env, "PWD=", path, data);
	update_env_var(data->env, "OLDPWD", old, data);
}
