/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_and_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:00:19 by hel-band          #+#    #+#             */
/*   Updated: 2024/08/15 13:00:19 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_exec	*create_cmd_arr(int *lex, t_list *token,
					int size, t_data *data);
static char		*copy_str(t_list *token);
static void		init_exec(t_exec *exec, int lex, int size);

int	is_redirect(int value)
{
	if (value == INFILE || value == OUTFILE
		|| value == HEREDOC || value == APPEND)
		return (1);
	return (0);
}

void	get_cmd_and_args(t_list *token, int *lexer, t_data *data)
{
	t_list	*temp;
	int		len;
	int		redirect;

	len = 0;
	redirect = 0;
	temp = token;
	while (temp != NULL && lexer[len] != PIPE)
	{
		if (lexer[len] == CMD)
			data->has_cmd = 1;
		else if (lexer[len] == BUILTIN)
			data->has_builtin = 1;
		else if (is_redirect(lexer[len]) == 1)
		{
			temp = temp->next;
			len++;
			redirect += 2;
		}
		temp = temp->next;
		len++;
	}
	data->len = len;
	if (data->has_cmd == 1 || data->has_builtin == 1)
		data->exec = create_cmd_arr(lexer, token, len - redirect, data);
}

static t_exec	*create_cmd_arr(int *lex, t_list *token, int size, t_data *data)
{
	int		i;
	int		j;
	t_exec	*exec;

	exec = ft_calloc(sizeof(t_exec), 1);
	init_exec(exec, lex[0], size);
	i = -1;
	j = 0;
	while (++i < data->len)
	{
		if (is_redirect(lex[i]) == 0)
		{
			if (lex[i] == CMD || lex[i] == BUILTIN)
				exec->lex = lex[i];
			exec->cmd[j++] = copy_str(token);
		}
		else
		{
			i++;
			token = token->next;
		}
		token = token->next;
	}
	update_last_command(data, exec->cmd[j - 1]);
	return (exec->cmd[j] = NULL, exec);
}

static void	init_exec(t_exec *exec, int lex, int size)
{
	exec->lex = lex;
	exec->fd_in = -2;
	exec->fd_out = -2;
	exec->cmd = ft_calloc(sizeof(char *), size + 1);
}

static char	*copy_str(t_list *token)
{
	char	*cmd;

	cmd = ft_calloc(sizeof(char), ft_strlen(token->content) + 1);
	ft_strlcpy(cmd, token->content, ft_strlen(token->content) + 1);
	return (cmd);
}
