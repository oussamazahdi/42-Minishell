/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:52:22 by hel-band          #+#    #+#             */
/*   Updated: 2024/08/15 12:52:22 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_free_str_arr(char ***arr)
{
	int	j;

	j = 0;
	while (*arr && (*arr)[j])
	{
		if ((*arr)[j])
		{
			free((*arr)[j]);
			(*arr)[j] = NULL;
		}
		j++;
	}
	if (*arr)
	{
		free(*arr);
		*arr = NULL;
	}
}
