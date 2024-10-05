/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_empty_nodes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:35:34 by ozahdi            #+#    #+#             */
/*   Updated: 2024/10/04 18:33:35 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_free_node(t_token **token)
{
	if (token && *token && (*token)->content)
		free((*token)->content);
	(*token)->content = NULL;
	if (token && *token)
		free(*token);
	*token = NULL;
}

static int	ft_clear_first(t_token **token)
{
	t_token	*ptr;

	ptr = *token;
	while (*token && (*token)->content && !ft_strlen((*token)->content) && \
		(*token)->flag == false)
	{
		(*token) = (*token)->next;
		ft_free_node(&ptr);
		ptr = *token;
	}
	if (!(*token))
		return (0);
	return (1);
}

int	ft_clear_empty_nodes(t_token **token, t_token *prev)
{
	t_token		*tmp;
	t_token		*ptr;

	if (!ft_clear_first(token))
		return (0);
	ptr = *token;
	while (ptr)
	{
		tmp = ptr->next;
		if (ptr && !ft_strlen(ptr->content) && ptr->flag == false)
		{
			ft_free_node(&ptr);
			if (prev)
				prev->next = tmp;
			ptr = tmp;
		}
		else
		{
			prev = ptr;
			if (ptr)
				ptr = ptr->next;
		}
	}
	return (1);
}
