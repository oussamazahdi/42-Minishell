/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:28:57 by ozahdi            #+#    #+#             */
/*   Updated: 2024/10/06 11:42:12 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_standar_syntax(char *read)
{
	char	*tmp;

	tmp = ft_remove_spaces(read);
	if (!ft_strcomp(tmp, "<< |") || !ft_strcomp(tmp, "<<|") || \
		!ft_strcomp(tmp, "< |") || !ft_strcomp(tmp, "<|") || \
		!ft_strcomp(tmp, ">> |") || !ft_strcomp(tmp, ">>|") || \
		!ft_strcomp(tmp, "> |") || !ft_strcomp(tmp, ">|") || \
		!ft_strcomp(tmp, "||") || !ft_strcomp(tmp, "| |") || \
		!ft_strcomp(tmp, "< <") || !ft_strcomp(tmp, "> >") || \
		!ft_strcomp(tmp, "<< <<") || !ft_strcomp(tmp, ">> >>") || \
		!ft_strcomp(tmp, "< >") || !ft_strcomp(tmp, "&") || \
		!ft_strcomp(tmp, "&&") || !ft_strcomp(tmp, "& &") || \
		!ft_strcomp(tmp, "(") || !ft_strcomp(tmp, "()") || \
		!ft_strcomp(tmp, "; |") || !ft_strcomp(tmp, ";|") || \
		!ft_strcomp(tmp, "> <") || !ft_strcomp(tmp, "( )") || \
		!ft_strcomp(tmp, "><"))
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}

static int	ft_multi_syntax(char *read)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (read[i])
	{
		while (ft_is_syntax(read[i]))
		{
			k++;
			i++;
		}
		if (k > 2)
			return (0);
		else
			k = 0;
		if (read[i])
			i++;
	}
	return (1);
}

static int	ft_check_syntax(t_data **line, char *read)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(read);
	if (read && read[ft_strlen(read) - 1] == '<' && \
		read[ft_strlen(read) - 2] == '<' && ft_strlen(read) == 2)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		(*line)->exit_status = 258;
		free(read);
		return (0);
	}
	if (len && (read[0] == '|' || read[len - 1] == '|' || \
		read[len - 1] == '>' || \
		(read[len - 1] == '<' && read[len - 2] != '<') || \
		!ft_multi_syntax(read) || !ft_standar_syntax(read)))
	{
		printf("minishell : syntax error near unexpected token\n");
		(*line)->exit_status = 258;
		free(read);
		return (0);
	}
	return (1);
}

static int	check_spaces(char *read)
{
	int		i;

	i = -1;
	while (read[++i])
		if (read[i] != ' ')
			return (1);
	return (0);
}

int	ft_parsing(t_data **line, char *read)
{
	if (read && !ft_strlen(read))
	{
		free(read);
		return (0);
	}
	if (!read || !ft_strlen(read) || !check_spaces(read) || \
		!ft_check_syntax(line, read) || !check_quotes(line, ft_chifr(read)))
		return (0);
	return (1);
}
