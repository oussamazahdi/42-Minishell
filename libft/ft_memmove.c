/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:16:25 by hel-band          #+#    #+#             */
/*   Updated: 2024/09/19 17:32:33 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memmove(void *dst, void *src, int len)
{
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)dst;
	s2 = (unsigned char *)src;
	if (!s1 && !s2)
		return (NULL);
	if (s2 < s1 && (s2 + len) > s1)
		while (len--)
			s1[len] = s2[len];
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
