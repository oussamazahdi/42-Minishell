/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:58:09 by hel-band          #+#    #+#             */
/*   Updated: 2024/08/15 12:58:09 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*ft_empty_env(void)
{
	t_list	*lst;

	lst = ft_init_pwd();
	if (!lst || !ft_init_shlvl_and_underscore(&lst)
		|| !ft_init_oldpwd_and_path(&lst))
	{
		ft_lstclear(&lst, free);
		return (NULL);
	}
	return (lst);
}

static char	*calculate_new_shlvl(char *shlvl_str)
{
	char	*new_shlvl;
	int		shlvl;

	shlvl = atoi(shlvl_str);
	if (shlvl > 999)
		shlvl = 0;
	else if (shlvl < 0)
		shlvl = -1;
	if (shlvl == 999)
		new_shlvl = ft_strdup("");
	else
		new_shlvl = ft_itoa(++shlvl);
	if (new_shlvl == NULL)
		perror("Memory allocation failed");
	return (new_shlvl);
}

static void	apply_new_shlvl(t_list *current, char *new_shlvl)
{
	char	*new_content;

	new_content = ft_strjoin("SHLVL=", new_shlvl);
	if (new_content == NULL)
	{
		free(new_shlvl);
		perror("Memory allocation failed");
		return ;
	}
	free(current->content);
	current->content = new_content;
	free(new_shlvl);
}

static void	update_shlvl(char *shlvl_str, t_list *current)
{
	char	*new_shlvl;

	new_shlvl = calculate_new_shlvl(shlvl_str);
	if (new_shlvl)
		apply_new_shlvl(current, new_shlvl);
}

void	check_shlvl(t_data *data)
{
	t_list	*current;

	if (data == NULL || data->env == NULL)
		return ;
	current = data->env;
	while (current)
	{
		if (strncmp("SHLVL=", (char *)current->content, 6) == 0)
		{
			update_shlvl((char *)current->content + 6, current);
			return ;
		}
		current = current->next;
	}
}
