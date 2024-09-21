/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:49:11 by hel-band          #+#    #+#             */
/*   Updated: 2024/09/19 18:00:50 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_substr(char *s, int start, int len)
{
	char	*dst;
	int		i;
	int		slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if ((int)start >= slen || len == 0)
		return (ft_calloc(1, 1));
	if (slen - (int)start <= len)
		len = slen - start;
	dst = malloc(len + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (s[start] && i < len)
		dst[i++] = s[start++];
	dst[i] = '\0';
	return (dst);
}
