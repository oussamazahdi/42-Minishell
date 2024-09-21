/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:38:30 by ozahdi            #+#    #+#             */
/*   Updated: 2024/09/18 12:02:09 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_env2(t_token **line)
{
	t_token		*env;

	env = (*line);
	while ((*line))
	{
		(*line) = (*line)->next;
		free(env->content);
		free(env->name);
		free(env->value);
		free(env);
		env = (*line);
	}
	(*line) = NULL;
}

void	ft_add_enver(t_data *data)
{
	t_list	*tmp;

	tmp = data->env;
	if (data->env_pars)
		ft_free_env2(&data->env_pars);
	while (tmp)
	{
		data->env_pars = addback_env(&data, tmp->content);
		tmp = tmp->next;
	}
}
