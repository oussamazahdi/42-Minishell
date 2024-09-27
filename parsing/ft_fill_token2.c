/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_token2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:20:23 by ozahdi            #+#    #+#             */
/*   Updated: 2024/09/25 14:47:00 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_arguments(t_data **line)
{
	t_token		*tmp;

	tmp = (*line)->pars_token;
	while (tmp)
	{
		if (tmp->type == -1)
			tmp->type = ARG;
		tmp = tmp->next;
	}
}

static void	ft_herdoc_append(t_data **line)
{
	t_token	*tmp;

	tmp = (*line)->pars_token;
	while (tmp)
	{
		if (tmp->content[0] == '>' && ft_strlen(tmp->content) == 2 && \
			tmp->next->content)
		{
			tmp->type = APPEND;
			tmp = tmp->next;
			tmp->type = APPEND;
		}
		if (tmp->content[0] == '<' && ft_strlen(tmp->content) == 2)
		{
			tmp->type = HEREDOC;
			if (tmp && tmp->next)
			{
				tmp = tmp->next;
				tmp->type = HEREDOC;
			}
		}
		tmp = tmp->next;
	}
}

static void	ft_in_out_pipe(t_data **line)
{
	t_token		*tmp;

	tmp = (*line)->pars_token;
	while (tmp)
	{
		if (tmp->content[0] == '<' && ft_strlen(tmp->content) == 1 && tmp->next)
		{
			tmp->type = INFILE;
			tmp = tmp->next;
			tmp->type = INFILE;
		}
		else if (tmp->content[0] == '>' && ft_strlen(tmp->content) == 1 && \
			tmp->next)
		{
			tmp->type = OUTFILE;
			tmp = tmp->next;
			tmp->type = INFILE;
		}
		else if (tmp->content[0] == '|')
			tmp->type = PIPE;
		tmp = tmp->next;
	}
}

static void	ft_builtings(t_data **line)
{
	t_token		*tmp;

	(*line)->builtin_check = 0;
	tmp = (*line)->pars_token;
	while (tmp)
	{
		if (tmp->type == CMD && (ft_compare(tmp->content, "echo") || \
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

void	ft_token_tmp(t_data **line)
{
	if ((*line)->pars_token && !(*line)->pars_token->next)
	{
		// (*line)->pars_token->content = \
		// 	ft_remove_quots((*line)->pars_token->content);
		(*line)->pars_token->type = CMD;
		ft_builtings(line);
		(*line)->process_count = 1;
		return ;
	}
	ft_in_out_pipe(line);
	ft_herdoc_append(line);
	ft_arguments(line);
	ft_commends(line);
	ft_builtings(line);
	if (herdoc_pars(line) > 33)
	{
		printf("minishell : maximum here-document count exceeded\n");
		exit (2);
	}
	ft_rederections(line);
}
