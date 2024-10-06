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
static int	print_export3(t_list *export);

int	check_key(char *var, t_data *data)
{
	int	i;
	int	plus;

	i = 0;
	plus = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
	{
		data->exit_status = 1;
		return (0);
	}
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (var[i] == '-')
			return (data->exit_status = 1, 0);
		if ((ft_isalnum(var[i]) == 0 && var[i] != '_'))
		{
			if (var[i] == '+' && var[i + 1] == '=')
				return (1);
			else
				return (data->exit_status = 1, 0);
		}
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
	if (print_export3(export) == 0)
	{
		while (export)
		{
			if (*flag != 1 && ft_strncmp("_=", (char *)export->content, 2) != 0
				&& (ft_strchr((char *)export->content, '=')
					|| ft_strncmp("OLDPWD", (char *)export->content, 6) == 0))
				print_export_entry(export->content);
			export = export->next;
		}
		return ;
	}
	while (export)
	{
		if (*flag != 1 && ft_strncmp("_=", (char *)export->content, 2) != 0)
			print_export_entry(export->content);
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
	if (print_export3(export) != 1)
	{
		while (export)
		{
			if (ft_strncmp("PATH=", (char *)export->content, 5) != 0
				&& ft_strncmp("_=", (char *)export->content, 2) != 0
				&& (ft_strchr((char *)export->content, '=')
					|| ft_strncmp("OLDPWD", (char *)export->content, 6) == 0))
				print_export_entry((char *)export->content);
			export = export->next;
		}
		return ;
	}
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

static int	print_export3(t_list *export)
{
	t_list	*temp;

	temp = export;
	while (temp)
	{
		if (ft_strncmp((char *)temp->content, "SHLVL=", 6) == 0)
		{
			if (ft_strchr((char *)temp->content, '1') != NULL)
				return (1);
			else if (ft_strchr((char *)temp->content, '2') != NULL)
				return (2);
			else
				return (0);
		}
		temp = temp->next;
	}
	return (1);
}
