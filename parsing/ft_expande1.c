/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expande1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:54:27 by ozahdi            #+#    #+#             */
/*   Updated: 2024/10/02 14:58:28 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_join_all(char *read, char *bfr, char *exp, int i)
{
	char	*aft;
	char	*new;

	aft = ft_substr(read, i, ft_strlen(read) - 1);
	if (exp)
	{
		new = ft_strjoin_pars(bfr, exp);
		new = ft_strjoin_pars(new, aft);
		free(read);
		read = NULL;
	}
	else
	{
		new = ft_strjoin_pars(bfr, aft);
		free(read);
		read = NULL;
	}
	if (aft)
		free(aft);
	aft = NULL;
	return (new);
}

static char	*ft_split_to_parts(t_data **line, char *read, int *status, int i)
{
	int		len;
	char	*bfr;
	char	*exp;
	char	*new;
	char	*aft;

	i = 0;
	len = 0;
	len = ft_parts_len(read, i);
	bfr = ft_substr(read, 0, len);
	i += len;
	exp = ft_extract_exp(read, &i, 0);
	aft = ft_substr(read, i, ft_strlen(read) - 1);
	new = ft_change_exp(*line, exp, aft, status);
	free(exp);
	exp = NULL;
	read = ft_join_all(read, bfr, new, i);
	free(new);
	new = ft_strdup(read);
	if (read)
		free(read);
	read = NULL;
	return (new);
}

static char	*ft_expande_process(char *read, int *status, t_data **line)
{
	char		*tmp;
	char		*dst;

	tmp = ft_strdup(read);
	if (read)
		free(read);
	read = NULL;
	dst = NULL;
	while (ft_check_expande(tmp))
	{
		dst = ft_split_to_parts(line, ft_strdup(tmp), status, 0);
		free(tmp);
		tmp = ft_strdup(dst);
		free(dst);
		dst = NULL;
	}
	free (dst);
	dst = NULL;
	return (tmp);
}

char	*ft_convert_not_expandebel(char *read)
{
	read = ft_convert_negatives(read);
	read = ft_goat(read);
	return (read);
}

char	*ft_expande(t_data **line, char *read)
{
	int		status;
	char	*tmp;

	tmp = NULL;
	if (!read || ft_strlen(read) == 0)
		return (NULL);
	read = ft_rebuild(read);
	status = 0;
	if (!ft_check_expande(read))
		return (read);
	while (ft_check_expande(read))
	{
		if (status == 0)
			read = ft_convert_not_expandebel(read);
		tmp = ft_expande_process(read, &status, line);
		read = ft_strdup(tmp);
		if (tmp)
			free(tmp);
		if (status == 0)
			read = ft_decode_double_quotes(read);
		status = 1;
	}
	read = chefer_v2(read);
	return (read);
}
