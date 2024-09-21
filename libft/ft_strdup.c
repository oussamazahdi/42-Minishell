/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:50:30 by hel-band          #+#    #+#             */
/*   Updated: 2024/09/19 18:01:25 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(char *s1)
{
	char	*dest;
	int		i;

	i = ft_strlen(s1);
	dest = malloc(i + 1);
	if (!dest)
		return (0);
	ft_memcpy(dest, s1, i);
	dest[i] = '\0';
	return (dest);
}
