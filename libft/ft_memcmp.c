/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:54:10 by hel-band          #+#    #+#             */
/*   Updated: 2024/09/19 17:55:59 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_memcmp(void *s1, void *s2, int n)
{
	unsigned char	*str;
	unsigned char	*dst;
	int				i;

	if (!n)
		return (0);
	i = 0;
	str = (unsigned char *)s1;
	dst = (unsigned char *)s2;
	while (i < n && str[i] == dst[i])
	{
		i++;
	}
	if (i == n)
		return (0);
	return (str[i] - dst[i]);
}
