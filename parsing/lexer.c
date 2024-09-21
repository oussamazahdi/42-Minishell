/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:42:45 by ozahdi            #+#    #+#             */
/*   Updated: 2024/09/19 17:10:43 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_token_size(t_token *token)
{
	t_token	*tmp;
	int		i;

	if (!token)
		return (0);
	tmp = token;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

static void	ft_fill_lexer(t_data **line, int size)
{
	t_token	*tmp;
	int		i;
	int		x;

	tmp = (*line)->pars_token;
	x = size;
	i = 0;
	while (x && tmp)
	{
		(*line)->lexer[i] = tmp->type;
		x--;
		i++;
		tmp = tmp->next;
	}
}

int	*ft_lexer(t_data **line)
{
	int		size;

	size = ft_token_size((*line)->pars_token);
	(*line)->lexer = malloc(size * sizeof(int));
	ft_fill_lexer(line, size);
	return ((*line)->lexer);
}
