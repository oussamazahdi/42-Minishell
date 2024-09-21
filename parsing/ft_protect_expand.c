/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_protect_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:11:22 by ozahdi            #+#    #+#             */
/*   Updated: 2024/09/20 15:45:52 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_code_singel_quotes(char *read)
{
	int		i;

	i = 0;
	read = ft_convert_negatives(read);
	while (read[i])
	{
		if (read[i] == 39)
		{
			i++;
			while (read[i] && read[i] != 39)
				read[i++] *= -1;
			if (read[i] && read[i] == 39)
				i++;
		}
		else
			i++;
	}
	return (read);
}

static t_token	*ft_handle_expansion(t_data **line, \
	t_token *token, t_token *befor)
{
	char		*dst;
	char		*ptr;

	dst = NULL;
	if (ft_check_expande(ft_code_singel_quotes(token->content)))
	{
		ptr = ft_strdup(token->content);
		dst = ft_expande(line, ptr);
		if (token && ft_strlen(dst) == 0 && (befor->type == APPEND || \
			befor->type == INFILE || befor->type == OUTFILE))
		{
			printf("minishell: %s: ambiguous redirect\n", token->content);
			(*line)->exit_status = 1;
			return (ft_free_all(line), free(dst), NULL);
		}
		free(token->content);
		token->content = ft_strdup(dst);
		free(dst);
		if (ft_check_args_spliting(ft_convert_negatives(token->content)))
		{
			token = ft_add_split_to_token(line, token, befor, \
				ft_convert_negatives(token->content));
		}
	}
	return (token);
}

static int	ft_clean_empty_tokens(t_data **line)
{
	t_token		*token;

	if (!(*line)->pars_token)
		return (0);
	token = (*line)->pars_token;
	while ((*line)->pars_token && ft_strlen((*line)->pars_token->content) == 0)
	{
		(*line)->pars_token = (*line)->pars_token->next;
		free(token->content);
		token->content = NULL;
		free(token);
		token = NULL;
		token = (*line)->pars_token;
	}
	if (!(*line)->pars_token)
	{
		(*line)->pars_token = NULL;
		return (0);
	}
	return (1);
}

int	ft_protect_expand(t_data **line)
{
	t_token		*token;
	t_token		*befor;

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
			token = ft_handle_expansion(line, token, befor);
		befor = token;
		if (token)
			token = token->next;
	}
	return (ft_clean_empty_tokens(line));
}
