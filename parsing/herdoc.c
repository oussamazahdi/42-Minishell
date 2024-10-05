/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:01:52 by ozahdi            #+#    #+#             */
/*   Updated: 2024/10/02 15:16:16 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_herdoc_syntax(t_data **line)
{
	printf("minishell: syntax error near unexpected token `newline'\n");
	(*line)->exit_status = 258;
	return (258);
}

static int	ft_herdoc_size(t_token *token)
{
	t_token	*tmp;
	int		size;

	size = 0;
	tmp = token;
	if (!token)
		return (0);
	while (tmp)
	{
		if (tmp->type == HEREDOC)
			size++;
		tmp = tmp->next;
	}
	return (size);
}

static int	ft_handle_heredoc_token(t_data **line, \
	t_token *token, char *direct, int i)
{
	char	*ptr;

	(*line)->fd_heredoc[i] = open(direct, O_CREAT | O_WRONLY | O_TRUNC, 0744);
	if ((*line)->fd_heredoc[i] == -1)
		return ((*line)->exit_status = 258, 0);
	ptr = ft_strdup(ft_convert_negatives(token->next->content));
	ft_write_infd(line, (*line)->fd_heredoc[i], ptr);
	if (g_herdoc == 1)
	{
		free((*line)->fd_heredoc);
		(*line)->fd_heredoc = NULL;
		free(direct);
		g_herdoc = 0;
		(*line)->exit_status = 1;
		return (0);
	}
	close((*line)->fd_heredoc[i]);
	return (1);
}

static int	ft_process_heredoc_tokens(t_data **line, \
	t_token *token, char *direct)
{
	int		i;

	i = 0;
	while (token)
	{
		if (token->type == HEREDOC && token->next && token->next->type == ARG)
		{
			if (!ft_handle_heredoc_token(line, token, direct, i))
				return (0);
			i++;
		}
		else if (token->type == HEREDOC && !token->next)
		{
			free(direct);
			ft_free_all(line);
			if ((*line)->fd_heredoc)
				free((*line)->fd_heredoc);
			(*line)->fd_heredoc = NULL;
			return (ft_herdoc_syntax(line));
		}
		token = token->next;
	}
	return (1);
}

int	herdoc(t_data **line)
{
	t_token		*token;
	char		*direct;
	int			heredoc_size;
	int			i;

	token = (*line)->pars_token;
	direct = ft_strdup("/tmp/herdoc.txt");
	heredoc_size = ft_herdoc_size(token);
	(*line)->fd_heredoc = malloc(heredoc_size * sizeof(int));
	i = ft_process_heredoc_tokens(line, token, direct);
	if (i == 0 || i == 258)
		return (ft_free_all(line), 0);
	free(direct);
	if ((*line)->fd_heredoc)
		free((*line)->fd_heredoc);
	(*line)->fd_heredoc = NULL;
	return (1);
}
