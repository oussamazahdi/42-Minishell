/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:59:18 by hel-band          #+#    #+#             */
/*   Updated: 2024/08/15 12:59:18 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_export2(t_list *export);
static void	print_export_entry(char *content);

void	export_builtin(t_data *data, char **args)
{
	t_list	*export;
	int		len;
	int		i;

	export = NULL;
	len = ft_arrsize(args);
	if (len == 1)
		sort_env(copy_env_list(data->env, export));
	else
	{
		i = 0;
		while (++i < len)
		{
			if (find_in_env(data, args[i]) == 0)
			{
				if (ft_strchr(args[i], '+'))
					args[i] = remove_plus(args[i]);
				ft_lstadd_back(&data->env,
					ft_lstnew_index(ft_strdup(args[i]), 1));
				data->exit_status = 0;
			}
		}
	}
	if (data->exit_status != 0)
		data->exit_status = 1;
}

int	check_key(char *var)
{
	int	i;
	int	plus;

	i = 0;
	plus = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (0);
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (var[i] == '-')
			return (0);
		if (ft_isalnum(var[i]) == 0 && var[i] != '_'
			&& (var[i] == '+' && var[i + 1] != '='))
			return (0);
		i++;
	}
	return (1);
}

void	print_export(t_list *export, int *flag)
{
	if (*flag == 1)
	{
		print_export2(export);
		return ;
	}
	while (export)
	{
		if (*flag != 1 && ft_strncmp("_=", (char *)export->content, 2) != 0)
		{
			print_export_entry(export->content);
		}
		export = export->next;
	}
}

static void	print_export_entry(char *content)
{
	char	*equals_sign;
	size_t	key_length;
	size_t	value_length;

	equals_sign = strchr(content, '=');
	if (equals_sign)
	{
		key_length = equals_sign - content;
		value_length = strlen(equals_sign + 1);
		write(STDOUT_FILENO, "declare -x ", 11);
		write(STDOUT_FILENO, content, key_length);
		write(STDOUT_FILENO, "=\"", 2);
		if (value_length > 0)
			write(STDOUT_FILENO, equals_sign + 1, value_length);
		write(STDOUT_FILENO, "\"\n", 2);
	}
	else
	{
		write(STDOUT_FILENO, "declare -x ", 11);
		write(STDOUT_FILENO, content, strlen(content));
		write(STDOUT_FILENO, "\n", 1);
	}
}

static void	print_export2(t_list *export)
{
	while (export)
	{
		if (ft_strncmp("PATH=", (char *)export->content, 5) != 0
			&& ft_strncmp("_=", (char *)export->content, 2) != 0)
		{
			print_export_entry((char *)export->content);
		}
		export = export->next;
	}
}
