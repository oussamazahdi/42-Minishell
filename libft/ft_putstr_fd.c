/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:47:48 by hel-band          #+#    #+#             */
/*   Updated: 2024/09/19 18:40:17 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int		i;

	i = 0;
	if (s == NULL)
		return (0);
	while (i < (int)ft_strlen(s))
	{
		write(fd, &s[i], 1);
		i++;
	}
	return (i);
}
