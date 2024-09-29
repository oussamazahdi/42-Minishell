/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:38:03 by ozahdi            #+#    #+#             */
/*   Updated: 2024/09/29 10:47:22 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_hundel_quotes(char *read)
{
	int		i;
	char	c;

	i = 0;
	if (read && ft_strlen(read) == 0)
		return (free(read), NULL);
	while (read[i])
	{
		if (read[i] == '"' || read[i] == 39)
		{
			c = read[i];
			i++;
			while (read[i] && read[i] != c)
				read[i++] *= -1;
			if (read[i] && read[i] == c)
				i++;
		}
		else
			read[i] *= -1;
		if (read[i] && read[i] != '"' && read[i] != 39)
			i++;
	}
	return (read);
}

char	*ft_change_and_join_quotes(char *read)
{
	char	**split;
	char	*new;
	int		i;

	i = -1;
	if (read == NULL)
		return (NULL);
	while (read[++i])
		if (read[i] == '"' || read[i] == 39)
			read[i] = -75;
	i = 0;
	split = ft_split_pars(read, -75);
	if (ft_arrsize(split) == 0)
		return (free(read), free(split), NULL);
	if (split[0] == NULL)
		return (free(split), NULL);
	new = NULL;
	while (split[i])
		new = ft_strjoin_pars(new, split[i++]);
	ft_free_double(split);
	split = NULL;
	free(read);
	read = NULL;
	return (new);
}

char	*ft_remove_quots(char *read)
{
	int		i;
	int		number;

	i = -1;
	number = 0;
	if (read == NULL)
		return (NULL);
	read = ft_chifr(read);
	while (read[++i])
		if (read[i] == '"' || read[i] == 39)
			number++;
	if (number == ft_strlen(read))
		return (free(read), NULL);
	read = ft_convert_negatives(read);
	read = ft_hundel_quotes(read);
	read = ft_change_and_join_quotes(read);
	read = ft_convert_negatives(read);
	return (read);
}

static int	condition_quotes(t_token *token)
{
	if (token->type == HEREDOC && token->next && \
		token->next->type == ARG)
		return (1);
	return (0);
}

void	ft_quotes_remove(t_data **line)
{
	t_token		*token;
	char		*new;

	token = (*line)->pars_token;
	while (token)
	{
		if (condition_quotes(token))
		{
			token = token->next;
			while (token && token->type == ARG)
				token = token->next;
		}
		else if (token && token->content)
		{
			new = ft_remove_quots(ft_convert_negatives(token->content));
			if (new && ft_strlen(new) > 0)
				token->content = ft_strdup(new);
			else if (!new)
				token->content = ft_strdup("");
			free(new);
			token = token->next;
		}
		else
			token = token->next;
	}
}
