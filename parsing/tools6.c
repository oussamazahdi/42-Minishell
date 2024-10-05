/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 10:44:26 by ozahdi            #+#    #+#             */
/*   Updated: 2024/10/02 15:40:30 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

char	*ft_chefer_v2_con(char *read, int *x, char c)
{
	int		i;

	i = *x;
	while (read[i] && read[i] != c)
	{
		if (read[i] > 0 && read[i] != c)
			read[i] *= -1;
		i++;
	}
	*x = i;
	return (read);
}

char	*chefer_v2(char *read)
{
	int		i;

	i = 0;
	if (!read)
		return (NULL);
	while (read && read[i])
	{
		if (read[i] > 0 && read[i] != 39 && read[i] != '"')
			read[i] *= -1;
		else if (read[i] && read[i] == 39)
		{
			i++;
			read = ft_chefer_v2_con(read, &i, 39);
		}
		else if (read[i] && read[i] == '"')
		{
			i++;
			read = ft_chefer_v2_con(read, &i, '"');
		}
		if (read[i])
			i++;
	}
	return (read);
}

int	ft_quotes_flag(char *read)
{
	int		i;

	i = 0;
	while (read[i])
	{
		if (read[i] == 34 || read[i] == 39)
			return (1);
		i++;
	}
	return (0);
}
