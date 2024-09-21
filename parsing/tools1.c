/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:04:16 by ozahdi            #+#    #+#             */
/*   Updated: 2024/09/19 11:11:13 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_collect(t_list *tmp)
{
	t_list		*src;
	char		*dst;

	src = tmp;
	dst = NULL;
	while (src)
	{
		dst = ft_strjoin_pars(dst, src->content);
		if (src && src->next)
			dst = ft_strjoin_pars(dst, " ");
		src = src->next;
	}
	return (dst);
}

void	ft_free_tmp(t_list *tmp)
{
	t_list		*o;

	o = tmp;
	while (tmp)
	{
		tmp = tmp->next;
		free(o->content);
		free(o);
		o = tmp;
	}
	tmp = (NULL);
}

int	ft_handle_syntax(char *read, int index)
{
	if (ft_is_syntax(read[index]))
	{
		if (read[index] == '|')
			index++;
		else if (read[index] == '>' || read[index] == '<')
			while (read[index] && ft_is_syntax(read[index]))
				index++;
	}
	else
	{
		while (read[index] && !ft_is_syntax(read[index]))
			index++;
	}
	return (index);
}

char	*ft_addspace(char *read, int index, int ptr)
{
	t_list		*tmp;
	t_list		*new;
	char		*coll;

	tmp = NULL;
	new = NULL;
	while (read[index])
	{
		index = ft_handle_syntax(read, index);
		new = ft_lstnew(ft_substr(read, ptr, index - ptr));
		ptr = index;
		if (!tmp)
			tmp = new;
		else
			ft_lstadd_back(&tmp, new);
	}
	coll = ft_collect(tmp);
	free(read);
	ft_free_tmp(tmp);
	return (coll);
}

int	ft_compare(char *s1, char *s2)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if ((!s1 && ft_strlen(s2) == 0))
		return (1);
	if (!s1 || !s2)
		return (0);
	while (s1[i])
	{
		if (ft_strlen(s1) != ft_strlen(s2) || (!s2[i] && s1[i]) || \
			(s1[i] != s2[i]))
			return (0);
		i++;
	}
	if (!s1[i] && s2[i])
		return (0);
	return (1);
}
