/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:12:29 by ozahdi            #+#    #+#             */
/*   Updated: 2024/09/29 10:43:57 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_remove_spaces2(char *read)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (read[i])
	{
		while (read[i] && read[i] != ' ')
		{
			i++;
			j++;
		}
		if (read[i] && (read[i] == ' ' || read[i] == '\t'))
			j++;
		while (read[i] && (read[i] == ' ' || read[i] == '\t'))
			i++;
	}
	return (j);
}

char	*ft_remove_spaces(char *read)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = ft_remove_spaces2(read);
	tmp = malloc(j + 1);
	j = 0;
	while (read[i])
	{
		while (read[i] && (read[i] == ' ' || read[i] == '\t'))
			i++;
		while (read[i] && read[i] != ' ' && read[i] != '\t')
			tmp[j++] = read[i++];
		while (read[i] && (read[i] == ' ' || read[i] == '\t'))
			i++;
		if (read[i])
			tmp[j++] = ' ';
	}
	tmp[j] = '\0';
	return (tmp);
}

int	ft_strcomp(char *src, char *cmp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!src || !cmp)
		return (0);
	while (src[i])
	{
		if (src[i] == cmp[j])
		{
			while (src[i] && cmp[j] && src[i] == cmp[j])
			{
				j++;
				i++;
			}
			if (!cmp[j])
				return (0);
			else
				j = 0;
		}
		else
			i++;
	}
	return (1);
}

static int	ft_parts_len2(char *read, int index)
{
	int		len;

	len = 0;
	while (read[index] && (ft_isalnum(read[index]) || \
		read[index] == '_' || read[index] == '$' || \
		read[index] == '?'))
	{
		if (ft_isalnum(read[index]) || read[index] == '_' || \
			read[index] == '?')
		{
			while (ft_isalnum(read[index]) || read[index] == '_' || \
				read[index] == '?')
			{
				index++;
				len++;
			}
			return (len);
		}
		index++;
		len++;
	}
	return (len);
}

int	ft_parts_len(char *read, int start)
{
	int		index;
	int		len;

	if (!read || ft_strlen(read) == 0)
		return (0);
	index = 0;
	len = 0;
	if (start == 0)
	{
		while (start == 0 && read[index] && read[index] != '$')
			index++;
		len = index;
	}
	else if (start != 0)
	{
		index = start;
		return (ft_parts_len2(read, index));
	}
	return (len);
}
