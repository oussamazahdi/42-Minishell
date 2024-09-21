/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_expande.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:45:32 by ozahdi            #+#    #+#             */
/*   Updated: 2024/09/18 12:59:36 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_herdoc_expande(char *read, int i)
{
	int		size;
	char	**ptr;
	char	*new;

	new = NULL;
	while (read[i])
	{
		while (read[i] && read[i] != '"' && read[i] != 39)
			i++;
		size = i - 1;
		while (read[size] && read[size] == '$')
			size--;
		if (read[i] && read[i - 1] && read[i - 1] == '$' && \
			(read[i] == '"' || read[i] == 39) && (i - size - 1) % 2 == 1)
			read[i - 1] = -72;
		if (read[i] == '"' || read[i] == 39)
			i++;
	}
	ptr = ft_split(read, -72);
	i = 0;
	while (ptr[i])
		new = ft_strjoin_pars(new, ptr[i++]);
	ft_free_double(ptr);
	return (new);
}
