/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:32:04 by ozahdi            #+#    #+#             */
/*   Updated: 2024/09/29 11:51:07 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_double(char **ptr)
{
	int		size;
	int		index;

	size = 0;
	index = 0;
	if (!ptr)
		return ;
	while (ptr[size])
		size++;
	while (index < size)
	{
		free(ptr[index]);
		ptr[index] = NULL;
		index++;
	}
	free(ptr);
	ptr = NULL;
}

static void	ft_free_pars_token(t_token **token)
{
	t_token		*tmp;

	tmp = (*token);
	while ((*token))
	{
		(*token) = (*token)->next;
		free(tmp->content);
		tmp->content = NULL;
		free(tmp);
		tmp = (*token);
	}
	(*token) = NULL;
}

static void	ft_free_env_pars(t_token **env)
{
	t_token		*tmp;

	tmp = (*env);
	while ((*env))
	{
		(*env) = (*env)->next;
		free(tmp->content);
		tmp->content = NULL;
		free(tmp->value);
		tmp->value = NULL;
		free(tmp->name);
		tmp->name = NULL;
		free(tmp);
		tmp = (*env);
	}
	(*env) = NULL;
}

static void	ft_free_token(t_list **token)
{
	t_list	*tmp;

	tmp = (*token);
	while ((*token))
	{
		(*token) = (*token)->next;
		free(tmp->content);
		tmp->content = NULL;
		free(tmp);
		tmp = (*token);
	}
	(*token) = NULL;
}

void	ft_free_all(t_data **line)
{
	if ((*line)->pars_token)
	{
		ft_free_pars_token(&(*line)->pars_token);
		(*line)->pars_token = NULL;
	}
	if ((*line)->env_pars)
	{
		ft_free_env_pars(&(*line)->env_pars);
		(*line)->env_pars = NULL;
	}
	if ((*line)->lexer)
	{
		free((*line)->lexer);
		(*line)->lexer = NULL;
	}
	if ((*line)->token)
	{
		ft_free_token(&(*line)->token);
		(*line)->token = NULL;
	}
}
