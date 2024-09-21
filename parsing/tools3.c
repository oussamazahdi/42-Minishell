/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:51:29 by ozahdi            #+#    #+#             */
/*   Updated: 2024/09/20 09:52:31 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_rebuild2(char *read, int *i)
{
	char	c;

	(*i) += 2;
	while (read[*i] == ' ')
		i++;
	while (read[*i] && read[*i] != ' ' && read[*i] != '<')
	{
		if (read[*i] == '"' || read[*i] == 39)
		{
			c = read[*i];
			if (read[*i])
				i++;
			while (read[*i] && read[*i] != c)
				read[(*i)++] *= -1;
		}
		else
			read[*i] *= -1;
		if (read[*i])
			i++;
	}
	return (read);
}

char	*ft_rebuild(char *read)
{
	int		i;

	read = ft_convert_negatives(read);
	i = 0;
	while (read[i])
	{
		if (read[i] == '<' && read[i + 1] == '<')
			read = ft_rebuild2(read, &i);
		else if (read[i] == '"')
		{
			i++;
			while (read[i] && read[i] != '"')
				i++;
		}
		else if (read[i] == 39)
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
	while (read[i])
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

char	*ft_strcpy(char *src, char *dst, int start, int end)
{
	int	i;

	i = 0;
	if (!src || start > end)
		return (NULL);
	while (start < end)
		dst[i++] = src[start++];
	dst[i] = '\0';
	return (dst);
}
