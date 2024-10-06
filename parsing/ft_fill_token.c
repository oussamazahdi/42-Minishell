/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:00:08 by ozahdi            #+#    #+#             */
/*   Updated: 2024/10/06 11:39:54 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_data	*ft_create_token(t_data **line, char *read)
{
	char		**ptr;
	int			i;

	ptr = ft_split_pars(read, ' ');
	i = 0;
	while (ptr[i])
	{
		(*line)->pars_token = ft_lstadd_back_pars((*line)->pars_token, ptr[i]);
		if (!(*line)->pars_token)
		{
			printf("minishell: malloc: memory allocation failed");
			exit (1);
		}
		i++;
	}
	free(read);
	ft_free_double(ptr);
	ft_token_tmp(line);
	return (*line);
}

int	ft_fill_token(t_data **line, char *read)
{
	t_token		*tmp;

	tmp = (*line)->pars_token;
	read = ft_addspace(read, 0, 0);
	ft_create_token(line, read);
	if (!line)
		return (0);
	if (!ft_protect_expand(line, tmp, NULL))
		return (0);
	ft_expande_export(line);
	tmp = (*line)->pars_token;
	while (tmp)
	{
		tmp->type = -1;
		tmp = tmp->next;
	}
	ft_token_tmp(line);
	return (1);
}
