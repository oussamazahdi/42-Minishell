/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:17:41 by ozahdi            #+#    #+#             */
/*   Updated: 2024/10/05 12:29:16 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_convert_to_negative(char *read)
{
	int	i;

	i = 0;
	while (read[i])
	{
		if (read[i] > 0)
			read[i] *= -1;
		i++;
	}
	return (read);
}

int	ft_check_expande(char *read)
{
	int		i;

	i = -1;
	if (!read)
		return (0);
	while (read[++i])
		if (read[i] == '$')
			return (1);
	return (0);
}

char	*ft_convert_negatives(char *read)
{
	int		i;

	i = 0;
	if (!read)
		return (NULL);
	while (read && read[i])
	{
		if (read[i] < 0)
			read[i] *= -1;
		i++;
	}
	return (read);
}

int	ft_check_args_spliting(char *read)
{
	int		i;

	i = 0;
	while (read[i])
	{
		if (read[i] == ' ' || read[i] == '\t')
		{
			while (read[i] && (read[i] == ' ' || read[i] == '\t'))
				i++;
			if (read[i] && read[i] != ' ' && read[i] != '\t' && read[i] != '\n')
				return (1);
			else if (!read[i])
				return (0);
		}
		i++;
	}
	return (0);
}

char	*ft_chifr(char *read)
{
	int		i;
	char	c;

	i = 0;
	read = ft_convert_negatives(read);
	while (read && read[i])
	{
		while (read[i] && read[i] != '"' && read[i] != 39)
			i++;
		if (i == ft_strlen(read))
			return (read);
		if (read[i] && (read[i] == '"' || read[i] == 39))
		{
			c = read[i++];
			while (read[i] && read[i] != c)
				read[i++] *= -1;
			if (read[i])
				i++;
		}
	}
	return (read);
}
