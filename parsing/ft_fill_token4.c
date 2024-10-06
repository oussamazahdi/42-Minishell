/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_token4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:34:27 by ozahdi            #+#    #+#             */
/*   Updated: 2024/10/06 13:25:32 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_check_pipe(t_token *tmp)
{
	while (tmp)
	{
		if (tmp->type == PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static char	*ft_last_command(t_data **line)
{
	t_token		*tmp;
	t_token		*before;

	if (ft_check_pipe((*line)->pars_token))
	{
		free((*line)->last_command);
		(*line)->last_command = ft_strdup("");
		return ((*line)->last_command);
	}
	tmp = (*line)->pars_token;
	before = (*line)->pars_token;
	while (tmp)
	{
		if ((tmp->type == ARG || tmp->type == BUILTIN || tmp->type == CMD) && \
			before->type != APPEND && before->type != HEREDOC && \
			before->type != INFILE && before->type != OUTFILE)
		{
			free((*line)->last_command);
			(*line)->last_command = ft_strdup(tmp->content);
		}
		before = tmp;
		tmp = tmp->next;
	}
	return ((*line)->last_command);
}

t_list	*ft_lstnew_token(char *content)
{
	t_list	*ptr;

	ptr = malloc(sizeof(t_list));
	if (!ptr || !content)
		return (NULL);
	content = ft_dechifre(content);
	if (content)
		ptr->content = ft_strdup(ft_convert_negatives(content));
	else
		ptr->content = ft_strdup("");
	ptr->next = NULL;
	return (ptr);
}

t_list	*ft_lstadd_back_token(t_list **token, char *ptr)
{
	t_list	*tmp;
	t_list	*new;

	tmp = (*token);
	new = ft_lstnew_token(ptr);
	if (!new)
		return (NULL);
	if (!tmp)
		(*token) = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->next = NULL;
	}
	return (*token);
}

void	ft_fill_struct(t_data **line)
{
	t_list	*tmp;
	t_token	*src;

	tmp = NULL;
	src = (*line)->pars_token;
	(*line)->last_command = ft_last_command(line);
	while (src)
	{
		tmp = ft_lstadd_back_token(&tmp, src->content);
		src = src->next;
	}
	(*line)->token = tmp;
}
