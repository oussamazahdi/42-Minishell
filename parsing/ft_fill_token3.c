/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_token3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:26:22 by ozahdi            #+#    #+#             */
/*   Updated: 2024/09/20 10:34:25 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_commends(t_data **line)
{
	t_token	*tmp;

	(*line)->process_count = 1;
	tmp = (*line)->pars_token;
	while (tmp)
	{
		while (tmp && tmp->type != ARG)
			tmp = tmp->next;
		if (tmp && tmp->type == ARG)
			tmp->type = CMD;
		while (tmp && tmp->type != PIPE)
			tmp = tmp->next;
		if (tmp && tmp->type == PIPE)
		{
			(*line)->process_count++;
		}
		if (tmp)
			tmp = tmp->next;
	}
}

int	herdoc_pars(t_data **line)
{
	t_token		*token;
	int			index;

	index = 0;
	token = (*line)->pars_token;
	while (token)
	{
		if (token->type == HEREDOC)
			index++;
		token = token->next;
	}
	return (index);
}

void	ft_rederections(t_data **line)
{
	t_token		*token;

	token = (*line)->pars_token;
	while (token)
	{
		if (token->type == INFILE || token->type == OUTFILE || \
		token->type == APPEND || token->type == HEREDOC)
		{
			if (token && token->next)
				token->next->type = ARG;
		}
		token = token->next;
	}
}
