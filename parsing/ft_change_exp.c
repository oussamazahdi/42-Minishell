/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_exp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:32:19 by ozahdi            #+#    #+#             */
/*   Updated: 2024/09/19 10:32:38 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_change_exp1(char *read, int *status, int *dollar, char *aft)
{
	int		i;

	i = 0;
	if (read[0] == '$' && !read[1] && ft_strlen(read) == 1 && \
		(*status) == 0 && ft_strlen(aft) > 0)
		return (NULL);
	while (read[i] && read[i] == '$')
		i++;
	if (i % 2 == 0)
		return (ft_convert_to_negative(read + i));
	else if (i % 2 == 1)
	{
		read += (i - 1);
		*dollar = i;
		return (ft_convert_negatives(read));
	}
	return (ft_convert_negatives(read));
}

static char	*ft_change_exp2(char *read, char *aft, int *status, int dollar)
{
	if (read[0] == '$' && read[1] && !ft_isalnum(read[1]) && \
		read[1] != '_' && read[1] != '?')
		return (ft_convert_to_negative(read));
	if (read[0] == '$' && !read[1] && ft_strlen(read) == 1 && \
		(*status) == 0 && ft_strlen(aft) > 0)
		return (NULL);
	if (read[0] == '$' && ft_strlen(read) == 1 && dollar > 1)
		return (ft_convert_to_negative(read));
	return (read);
}

char	*ft_change_exp(t_data *line, char *read, char *aft, int *status)
{
	int			i;
	char		*exp;

	i = 0;
	read = ft_change_exp1(read, status, &i, aft);
	if (!read || (read && ft_check_negatives(read)))
		return (free(aft), ft_strdup(read));
	read = ft_change_exp2(read, aft, status, i);
	if (!read || (read && ft_check_negatives(read)))
		return (free(aft), ft_strdup(read));
	if (read && read[1] && (ft_isdigit(read[1]) || read[1] == '?'))
	{
		if (ft_isdigit(read[1]))
			return (free(aft), ft_strdup(read + 2));
		else if (read[1] == '?')
			return (free(aft), ft_convert_to_negative(\
				ft_strjoin_pars(ft_itoa(line->exit_status), read + 2)));
	}
	if (read[0] == '$' && ft_strlen(read) == 1 && ((*status) || \
		((*status) == 0 && !aft[0])))
		return (free(aft), ft_convert_to_negative(ft_strdup(read)));
	exp = ft_change(read + 1, line->env_pars, NULL, line);
	free(aft);
	return (exp);
}
