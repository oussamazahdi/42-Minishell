/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expande_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:18:59 by ozahdi            #+#    #+#             */
/*   Updated: 2024/09/29 11:58:37 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	expand_tilde_to_home(t_data **line, t_token *token)
{
	t_token		*env;
	char		*tmp;

	if (token && token->content && token->content[0] == '~' && \
		(!token->content[1] || token->content[1] == '/'))
	{
		env = (*line)->env_pars;
		while (env)
		{
			if (ft_compare(env->name, "HOME"))
			{
				tmp = ft_strdup(token->content + 1);
				free(token->content);
				token->content = ft_strjoin_pars(ft_strdup(env->value), tmp);
				free(tmp);
				tmp = NULL;
				break ;
			}
			env = env->next;
		}
	}
}

static void	handle_export_and_expand_args(t_data **line, t_token **token, \
	t_token **befor)
{
	int		sp;

	while ((*token) && (*token)->type == ARG)
	{
		sp = ft_check_spliting(ft_convert_negatives((*token)->content));
		(*token)->content = ft_remove_quots((*token)->content);
		if (ft_check_expande(ft_convert_negatives((*token)->content)))
			(*token)->content = ft_expande(line, \
			ft_convert_negatives((*token)->content));
		if (!sp && ft_strlen((*token)->content) > 0)
		{
			ft_add_to_list(*befor, ft_convert_negatives((*token)->content));
			(*token) = (*befor)->next;
		}
		(*befor) = (*token);
		(*token) = (*token)->next;
	}
}

void	ft_expande_export(t_data **line)
{
	t_token		*token;
	t_token		*befor;

	token = (*line)->pars_token;
	befor = (*line)->pars_token;
	while (token)
	{
		expand_tilde_to_home(line, token);
		if (token && token->type == BUILTIN && \
			ft_compare(token->content, "export"))
		{
			befor = token;
			token = token->next;
			handle_export_and_expand_args(line, &token, &befor);
		}
		else if (token && token->rm_quotes == false && \
			befor && befor->type != HEREDOC)
			token->content = ft_remove_quots(token->content);
		befor = token;
		if (token)
			token = token->next;
	}
}
