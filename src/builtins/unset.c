/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:59:42 by hel-band          #+#    #+#             */
/*   Updated: 2024/08/15 12:59:42 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_find(t_data *data, char *arr);
static void	ft_free_node(t_list **node, t_list **list);
static bool	ft_check(char *var);

void	unset_builtin(t_data *data, char **args)
{
	int	i;

	i = 0;
	while (args[++i] != NULL && ft_strncmp(args[1], "_", 1) != 0)
	{
		if (!ft_check(args[i]) || ft_strchr(args[i], '=') != NULL)
		{
			printf("minishell: unset: `%s': not a valid identifier\n", args[i]);
			data->exit_status = 1;
			return ;
		}
		else
		{
			ft_find(data, args[i]);
		}
	}
	if (ft_arrsize(args) > 30)
	{
		free_list(data->env);
		data->env = NULL;
	}
	data->exit_status = 0;
}

static void	ft_find(t_data *data, char *arr)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = data->env;
	prev = NULL;
	while (tmp)
	{
		if (ft_strncmp((char *)tmp->content, arr, ft_strlen(arr)) == 0
			&& (((char *)tmp->content)[ft_strlen(arr)] == '='
			|| ((char *)tmp->content)[ft_strlen(arr)] == '\0'))
		{
			ft_free_node(&tmp, &data->env);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	ft_free_node(t_list **node, t_list **list)
{
	t_list	*temp;

	if (*list == *node)
	{
		temp = (*list)->next;
		free((*node)->content);
		free(*node);
		*list = temp;
	}
	else
	{
		temp = *list;
		while (temp && temp->next != *node)
			temp = temp->next;
		if (temp)
		{
			temp->next = temp->next->next;
			free((*node)->content);
			free(*node);
		}
	}
}

static bool	ft_check(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (false);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
