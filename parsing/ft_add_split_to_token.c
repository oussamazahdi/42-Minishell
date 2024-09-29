/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_split_to_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:35:23 by ozahdi            #+#    #+#             */
/*   Updated: 2024/09/29 10:45:50 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**process_input_string(char *read)
{
	char		**ptr;

	read = ft_convert_negatives(read);
	read = ft_chifr(read);
	ptr = ft_split_pars(read, ' ');
	return (ptr);
}

t_token	*create_token_list(char **ptr)
{
	t_token		*tmp;
	int			i;

	tmp = NULL;
	i = 0;
	while (ptr[i])
	{
		ptr[i] = ft_convert_negatives(ptr[i]);
		tmp = ft_lstadd_back_pars2(tmp, ptr[i]);
		i++;
	}
	return (tmp);
}

void	replace_or_insert_token(t_data **line, \
	t_token **token, t_token *tmp)
{
	t_token		*after;

	if (!(*token)->next)
	{
		free((*line)->pars_token->content);
		free((*line)->pars_token);
		(*line)->pars_token = tmp;
	}
	else
	{
		after = (*token)->next;
		free((*token)->content);
		(*token)->content = ft_strdup(tmp->content);
		(*token)->next = tmp->next;
		free(tmp->content);
		free(tmp);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = after;
		while (after->next)
			after = after->next;
		after->next = NULL;
	}
}

void	update_token_pointers(t_token **befor, t_token **token, t_token *tmp)
{
	t_token		*after;

	if (!(*token)->next)
	{
		free((*token)->content);
		free(*token);
		(*token) = (*befor);
		(*token)->next = tmp;
		while ((*befor)->next)
			(*befor) = (*befor)->next;
		(*token) = (*token)->next;
		(*befor)->next = NULL;
	}
	else
	{
		after = (*token)->next;
		free((*token)->content);
		free(*token);
		*token = tmp;
		(*befor)->next = *token;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = after;
	}
}

t_token	*ft_add_split_to_token(t_data **line, t_token *token, \
	t_token *befor, char *read)
{
	char		**ptr;
	t_token		*tmp;

	ptr = process_input_string(read);
	tmp = create_token_list(ptr);
	ft_free_double(ptr);
	if (befor == token)
		replace_or_insert_token(line, &token, tmp);
	else if (befor != token)
		update_token_pointers(&befor, &token, tmp);
	return (token);
}
