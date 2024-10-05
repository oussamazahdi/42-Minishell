/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:51:29 by ozahdi            #+#    #+#             */
/*   Updated: 2024/10/02 14:54:15 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_rebuild2(char *read, int *i)
{
	char	c;
	int		j;

	j = *i + 2;
	while (read && read[j] && read[j] == ' ')
		j++;
	while (read[j] && read[j] != ' ' && read[j] != '<')
	{
		if (read[j] && (read[j] == '"' || read[j] == 39))
		{
			c = read[j];
			if (read[j])
				j++;
			while (read[j] && read[j] != c)
				read[j++] *= -1;
		}
		else
			read[j] *= -1;
		if (read[j])
			j++;
	}
	*i = j;
	return (read);
}

char	*ft_rebuild(char *read)
{
	int		i;

	read = ft_convert_negatives(read);
	i = 0;
	while (read[i])
	{
		if (read [i] && read[i] == '<' && read[i + 1] && read[i + 1] == '<')
			read = ft_rebuild2(read, &i);
		else if (read [i] && read[i] == '"')
		{
			i++;
			while (read[i] && read[i] != '"')
				i++;
		}
		else if (read [i] && read[i] == 39)
			while (read[++i] && read[i] != 39)
				read[i] *= -1;
		if (read[i] && (read[i] != '<' || (read[i] == '<' && \
			read[i + 1] != '<')))
			i++;
	}
	return (read);
}

char	*ft_code_double_quotes(char *read)
{
	int		i;

	i = 0;
	while (read && read[i])
	{
		while (read[i] && read[i] != '"')
			i++;
		if (read[i] && read[i] == '"')
			i++;
		while (read[i] && read[i] != '"')
		{
			if (read[i] > 0)
				read[i] *= -1;
			i++;
		}
		if (read[i] && read[i] == '"')
			i++;
	}
	return (read);
}

char	*ft_code_singel_quotes(char *read)
{
	int		i;

	i = 0;
	while (read && read[i])
	{
		while (read[i] && read[i] != 39)
			i++;
		if (read[i] && read[i] == 39)
			i++;
		while (read[i] && read[i] != 39)
		{
			if (read[i] > 0)
				read[i] *= -1;
			i++;
		}
		if (read[i] && read[i] == 39)
			i++;
	}
	return (read);
}

char	*ft_decode_double_quotes(char *read)
{
	int		i;

	i = 0;
	while (read[i])
	{
		while (read[i] && read[i] != '"')
			i++;
		if (read[i] && read[i] == '"')
			i++;
		while (read[i] && read[i] != '"')
		{
			if (read[i] < 0)
				read[i] *= -1;
			i++;
		}
		if (read[i] && read[i] == '"')
			i++;
	}
	return (read);
}
