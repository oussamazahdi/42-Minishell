/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_protect_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:11:22 by ozahdi            #+#    #+#             */
/*   Updated: 2024/10/05 17:12:51 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_sp(char *read)
{
	int		i;
	char	*ptr;

	i = 0;
	// printf("ptr bfr : [%s]\n", ft_convert_negatives(read));
	ptr = ft_strtrim(ft_convert_negatives(read), " \t");
	// printf("ptr aft : [%s]\n", ptr);
	// printf("ptr aft : [%s]\n", ft_convert_negatives(read));
	while (ptr && ptr[i] && (ptr[i] == ' ' || ptr[i] == '\t'))
		i++;
	if (i == ft_strlen(ptr))
		return (free(ptr), ptr = NULL, 1);
	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == ' ' || ptr[i] == '\t')
			return (free(ptr), ptr = NULL, 1);
		i++;
	}
	return (free(ptr), ptr = NULL, 0);
}

char	*ft_goat(char *read)
{
	int		i;
	char	c;

	i = 0;
	if (!read)
		return (NULL);
	while (read[i])
	{
		if (read[i] == 34 || read[i] == 39)
		{
			c = read[i];
			i++;
			while (read[i] && read[i] != c)
			{
				if (read[i] > 0 && read[i] != c)
					read[i] *= -1;
				i++;
			}
			if (read[i] && read[i] == c)
				i++;
		}
		else
			i++;
	}
	return (read);
}

static t_token	*ft_handle_expansion(t_data **line, \
	t_token *token, t_token *befor, char *dst)
{
	char		*ptr;

	if (ft_check_expande(ft_convert_negatives(token->content)))
	{
		ptr = ft_strdup(token->content);
		dst = ft_expande(line, ptr);
		dst = ft_change_and_join_quotes(ft_goat(dst));
		if (token && (ft_strlen(dst) == 0 || ft_sp(dst)) && (befor->type == \
			APPEND || befor->type == INFILE || befor->type == OUTFILE))
		{
			ft_putstr_fd("minishell: ambiguous redirect\n", 2);
			// printf("minishell: %s: ambiguous redirect\n", token->content);
			(*line)->exit_status = 1;
			return (ft_free_all(line), free(dst), NULL);
		}
		free(token->content);
		token->content = ft_strdup(dst);
		token->rm_quotes = true;
		free(dst);
		if (ft_check_args_spliting(ft_convert_negatives(token->content)))
			token = ft_add_split_to_token(line, token, befor, \
				ft_convert_negatives(token->content));
	}
	else
		token->content = ft_remove_quots(ft_convert_negatives(token->content));
	return (token);
}

int	ft_protect_expand(t_data **line, t_token *token, t_token *befor)
{
	token = (*line)->pars_token;
	befor = (*line)->pars_token;
	while (token)
	{
		if (token && (ft_compare(token->content, "export") || \
			token->type == HEREDOC))
		{
			if (token)
				token = token->next;
			if (token && befor->type == HEREDOC)
				token->content = ft_convert_to_negative(token->content);
			else if (token && befor->type == BUILTIN)
				while (token && token->type == ARG)
					token = token->next;
		}
		else
		{
			token = ft_handle_expansion(line, token, befor, NULL);
			if (!token)
				return (0);
		}
		befor = token;
		if (token)
			token = token->next;
	}
	return (ft_clear_empty_nodes(&(*line)->pars_token, NULL));
}
