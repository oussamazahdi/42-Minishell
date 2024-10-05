/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tools1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:17:50 by ozahdi            #+#    #+#             */
/*   Updated: 2024/10/02 15:40:45 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*newnode_env(char *ptr)
{
	t_token		*new;
	int			i;

	i = 0;
	if (!ptr || ft_strlen(ptr) == 0)
		return (NULL);
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = ft_strdup(ptr);
	while (ptr[i] && ptr[i] != '=')
		i++;
	new->name = ft_substr(ptr, 0, i);
	new->value = ft_substr(ptr, i + 1, ft_strlen(ptr) - i - 1);
	new->type = 0;
	new->next = NULL;
	return (new);
}

t_token	*addback_env(t_data **line, char *ptr)
{
	t_token	*tmp;
	t_token	*new;

	new = newnode_env(ptr);
	if (!new)
		return (NULL);
	if (!(*line)->env_pars)
		(*line)->env_pars = new;
	else
	{
		tmp = (*line)->env_pars;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->next = NULL;
	}
	return ((*line)->env_pars);
}

t_token	*ft_lstnew_pars(char *content)
{
	t_token	*ptr;

	ptr = malloc(sizeof(t_list));
	if (!ptr || !content)
		return (NULL);
	content = ft_dechifre(content);
	ptr -> content = ft_strdup(content);
	ptr -> name = NULL;
	ptr -> value = NULL;
	ptr -> type = -1;
	ptr -> rm_quotes = false;
	ptr -> next = NULL;
	return (ptr);
}

t_token	*ft_lstadd_back_pars2(t_token *lst, char *ptr)
{
	t_token	*tmp;
	t_token	*new;

	tmp = lst;
	new = ft_lstnew_pars(ptr);
	new->rm_quotes = true;
	if (!new)
		return (NULL);
	if (!tmp)
		lst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->next = NULL;
	}
	return (lst);
}

// int	ft_quotes_flag(char *read)
// {
// 	int		i;

// 	i = 0;
// 	while (read[i])
// 	{
// 		if (read[i] == 34 || read[i] == 39)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

t_token	*ft_lstadd_back_pars(t_token *lst, char *ptr)
{
	t_token	*tmp;
	t_token	*new;

	tmp = lst;
	new = ft_lstnew_pars(ptr);
	if (ft_quotes_flag(ptr) == 1)
		new->flag = true;
	else
		new->flag = false;
	if (!new)
		return (NULL);
	if (!tmp)
		lst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->next = NULL;
	}
	return (lst);
}
