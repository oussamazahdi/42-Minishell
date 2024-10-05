/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:52:55 by ozahdi            #+#    #+#             */
/*   Updated: 2024/10/05 15:38:07 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_quotes(t_data **line, char *read)
{
	int		i;
	int		k;
	int		s;

	i = 0;
	s = 0;
	k = 0;
	while (read[i])
	{
		if (read[i] && read[i] == '"')
			k++;
		if (read[i] && read[i] == '\'')
			s++;
		if (read[i])
			i++;
	}
	if (k % 2 != 0 || s % 2 != 0)
	{
		ft_putstr_fd("minishell: syntax error unexpected end of file", 2);
		(*line)->exit_status = 258;
		free(read);
		return (0);
	}
	return (1);
}
