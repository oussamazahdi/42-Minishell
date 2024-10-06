/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expande2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:01:55 by ozahdi            #+#    #+#             */
/*   Updated: 2024/10/06 11:39:31 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_condition1(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '?')
		return (1);
	return (0);
}

static int	ft_condition2(char c)
{
	if (c != ' ' && c != '$' && c != '"' && c != 39)
		return (1);
	return (0);
}

char	*ft_extract_exp(char *read, int *i, int last)
{
	char	*exp;

	while (read[(*i)] != '$')
		i++;
	last = (*i) + 1;
	while (read[last])
	{
		while (read[last] && read[last] == '$')
			last++;
		if (read[last] && ft_condition1(read[last]))
		{
			while (read[last] && ft_condition1(read[last]))
				last++;
			break ;
		}
		else if (read[last] && !ft_condition1(read[last]))
		{
			while (read[last] && ft_condition2(read[last]))
				last++;
			break ;
		}
	}
	exp = ft_substr(read, *i, last - *i);
	(*i) = last;
	return (exp);
}
