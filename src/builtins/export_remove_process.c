/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_split_key_and_value.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:58:47 by hel-band          #+#    #+#             */
/*   Updated: 2024/08/15 12:58:47 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remove_plus(char *str)
{
	int		flag;
	int		i;
	int		len;
	int		result_len;
	char	*result;

	flag = 0;
	i = -1;
	len = strlen(str);
	result_len = 0;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	while (++i < len)
	{
		if (str[i] == '+' && flag == 0)
		{
			i++;
			flag = 1;
		}
		result[result_len++] = str[i];
	}
	result[result_len] = '\0';
	return (result);
}

static void	perform_sorting(t_list *export)
{
	t_list	*temp1;
	t_list	*temp2;
	int		swapped;

	temp2 = NULL;
	while (true)
	{
		temp1 = export;
		swapped = 0;
		while (temp1->next != temp2)
		{
			if (ft_strcmp(temp1->content, temp1->next->content) > 0)
			{
				ft_swap_lst(temp1);
				swapped = 1;
			}
			temp1 = temp1->next;
		}
		temp2 = temp1;
		if (!swapped)
			break ;
	}
}

void	sort_env(t_list *export)
{
	t_list	*temp1;
	int		flag;

	temp1 = export;
	flag = 0;
	while (temp1)
	{
		if (temp1->index == 2)
		{
			flag = 1;
			break ;
		}
		temp1 = temp1->next;
	}
	perform_sorting(export);
	print_export(export, &flag);
	free_list(export);
}

int	find_in_env(t_data *data, char *var)
{
	t_list	*temp;
	char	**arr;
	int		result;

	data->var = var;
	temp = data->env;
	if (check_key(var, data) == 0)
	{
		ft_printf_fd(2, "minishell: export: `%s': not a valid identifier\n", \
		var);
		data->exit_status = 1;
		return (2);
	}
	arr = ft_split(var, '=');
	result = search_key(temp, arr, var, data);
	ft_free_str_arr(&arr);
	arr = NULL;
	return (result);
}

t_list	*copy_env_list(t_list *env, t_list *lst)
{
	t_list	*new_node;

	while (env != NULL)
	{
		new_node = ft_lstnew_index(ft_strdup(env->content), env->index);
		if (!new_node || !new_node->content)
		{
			ft_lstclear(&lst, free);
			return (NULL);
		}
		ft_lstadd_back(&lst, new_node);
		env = env->next;
	}
	return (lst);
}
