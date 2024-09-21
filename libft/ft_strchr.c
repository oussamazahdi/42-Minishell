/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 09:51:22 by hel-band          #+#    #+#             */
/*   Updated: 2024/09/19 17:46:03 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strchr(char *s, int c)
{
	int		i;
	char	uc;

	uc = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == uc)
			return ((char *) &s[i]);
		i++;
	}
	if (!uc)
		return ((char *) &s[i]);
	return (NULL);
}
