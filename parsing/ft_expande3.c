/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expande3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:04:42 by ozahdi            #+#    #+#             */
/*   Updated: 2024/09/20 09:55:40 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_change(char *expande, t_token *env, t_token *tmp, t_data *line)
{
	if (!expande || ft_strlen(expande) == 0)
		return (NULL);
	tmp = env;
	if (ft_strlen(expande) == 1 && expande[0] == '_')
	{
		expande = ft_strdup(line->last_command);
		expande = ft_convert_to_negative(expande);
		return (expande);
	}
	while (tmp)
	{
		if (ft_strlen(expande) == ft_strlen(tmp->name) && ft_compare(expande, \
			tmp->name))
		{
			expande = ft_strdup(tmp->value);
			expande = ft_convert_to_negative(expande);
			return (expande);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

t_token	*ft_create_token_list(char *read)
{
	t_token		*token;
	t_token		*tmp;
	char		**ptr;
	int			i;

	i = -1;
	tmp = NULL;
	ptr = ft_split_pars(read, ' ');
	while (ptr && ptr[++i])
		tmp = ft_lstadd_back_pars(tmp, ptr[i]);
	ft_free_double(ptr);
	token = tmp;
	while (token)
	{
		token->type = ARG;
		token = token->next;
	}
	return (tmp);
}

void	ft_add_to_list(t_token *befor, char *read)
{
	t_token		*token;
	t_token		*after;
	t_token		*tmp;

	tmp = ft_create_token_list(read);
	if (!tmp)
		return ;
	token = befor->next;
	after = token->next;
	befor->next = tmp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = after;
	free(token->content);
	token->content = NULL;
	free(token);
	token = NULL;
}
