/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:23:59 by ozahdi            #+#    #+#             */
/*   Updated: 2024/10/06 15:23:56 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_herdoc_expanding(char *read)
{
	int		i;

	i = -1;
	if (!read)
		return (1);
	while (read[++i])
		if (read[i] == '"' || read[i] == 39)
			return (1);
	return (0);
}

static int	ft_herdoc_g_var(char *ptr, char *res, char *file, int fd)
{
	if (g_herdoc == 1)
	{
		free(ptr);
		free(file);
		free(res);
		close (fd);
		res = NULL;
		ptr = NULL;
		file = NULL;
		return (0);
	}
	return (1);
}

static char	*ft_prepare_file_content(char *file)
{
	char	*file2;

	file = ft_chifr(file);
	file2 = ft_herdoc_expande(file, 0);
	free(file);
	file2 = ft_remove_quots(file2);
	if (file2 && ft_strlen(file2) == 0)
	{
		free(file2);
		file2 = NULL;
	}
	return (file2);
}

static char	*ft_fill_res(char *ptr, char *file, int fd, int *status)
{
	char	*res;

	res = NULL;
	while (1)
	{
		signal(SIGINT, sigint_heredoc);
		ptr = readline("> ");
		if (!ft_herdoc_g_var(ptr, res, file, fd))
		{
			*status = 0;
			ptr = NULL;
			return (NULL);
		}
		if (!ptr || (!ft_strlen(ptr) && !ft_strlen(file)) || \
			((ft_strlen(ptr) == ft_strlen(file)) && ft_compare(file, ptr)))
			break ;
		else if (ptr && ft_strlen(ptr) == 0)
			res = ft_strjoin_pars(res, "\n");
		else
			res = ft_strjoin_pars(ft_strjoin_pars(res, ptr), "\n");
		free(ptr);
	}
	if (ptr)
		free(ptr);
	return (res);
}

int	ft_write_infd(t_data **line, int fd, char *file)
{
	char	*ptr;
	char	*res;
	int		check;
	int		status;

	status = 1;
	ptr = NULL;
	check = 0;
	check = ft_check_herdoc_expanding(file);
	file = ft_prepare_file_content(file);
	res = ft_fill_res(ptr, file, fd, &status);
	if (!status)
		return (0);
	if (check == 0)
		res = ft_normal_expand(ft_expande(line, res), line);
	if (res)
	{
		ft_putstr_fd(res, fd);
		free(res);
	}
	return (free(file), 1);
}
