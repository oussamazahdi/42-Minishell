/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_token3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:26:22 by ozahdi            #+#    #+#             */
/*   Updated: 2024/10/06 11:40:58 by ozahdi           ###   ########.fr       */
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
		{
			if (tmp->type == PIPE)
				(*line)->process_count++;
			tmp = tmp->next;
		}
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

static char	*extract_str(t_token *tmp)
{
	char	*str;

	if (tmp->type == CMD && tmp->content && tmp->content[0] == 34)
		str = ft_substr(tmp->content, 1, ft_strlen(tmp->content) - 2);
	else if (tmp->type == CMD && tmp->content && tmp->content[0] == 39)
		str = ft_substr(tmp->content, 1, ft_strlen(tmp->content) - 2);
	else
		str = ft_strdup(tmp->content);
	return (str);
}

void	ft_builtings(t_data **line)
{
	t_token		*tmp;
	char		*str;

	(*line)->builtin_check = 0;
	tmp = (*line)->pars_token;
	while (tmp)
	{
		str = extract_str(tmp);
		free(tmp->content);
		tmp->content = ft_strdup(str);
		free(str);
		if (tmp && tmp->type == CMD && (ft_compare(tmp->content, "echo") || \
			ft_compare(tmp->content, "export") || \
			ft_compare(tmp->content, "pwd") || \
			ft_compare(tmp->content, "unset") || \
			ft_compare(tmp->content, "env") || \
			ft_compare(tmp->content, "exit") || \
			ft_compare(tmp->content, "cd")))
		{
			(*line)->builtin_check = 1;
			tmp->type = BUILTIN;
		}
		tmp = tmp->next;
	}
}
