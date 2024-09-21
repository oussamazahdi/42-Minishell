/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:00:45 by ozahdi            #+#    #+#             */
/*   Updated: 2024/09/18 13:10:33 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_negatives(char *read)
{
	int		i;

	i = 0;
	while (read[i])
	{
		if (read[i] > 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_spliting(char *read)
{
	int		i;

	i = -1;
	if (!read)
		return (1);
	while (read[++i])
		if (read[i] == '=')
			return (1);
	i = -1;
	while (read[++i])
		if (read[i] == '"' || read[i] == 39)
			return (1);
	return (0);
}

char	*ft_dechifre(char *ptr)
{
	int		i;

	i = 0;
	if (ptr[i] && (ptr[0] == '"' || ptr[0] == '\''))
	{
		while (ptr[i])
		{
			if (ptr[i] < 0)
				ptr[i++] *= -1;
			else
				i++;
		}
	}
	return (ptr);
}

char	*ft_strjoin_pars(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 0;
	if (!s1 || !s2)
	{
		if (!s1)
			s1 = ft_strdup("");
		else
			return (s1);
	}
	ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		return (NULL);
	while (s1[j])
		ptr[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	if (s1)
		free(s1);
	return (s1 = NULL, ptr);
}

int	ft_is_syntax(int c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}
