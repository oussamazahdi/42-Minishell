/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_with_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:01:18 by hel-band          #+#    #+#             */
/*   Updated: 2024/08/15 13:01:18 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	redirect_files(int fd_in, int fd_out)
{
	if (fd_in != -2)
		dup2(fd_in, 0);
	if (fd_out != -2)
		dup2(fd_out, 1);
}

void	close_files(int fd_in, int fd_out)
{
	if (fd_in != -2)
		close(fd_in);
	if (fd_out != -2)
		close(fd_out);
}
