/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:59:10 by hel-band          #+#    #+#             */
/*   Updated: 2024/08/31 13:28:26 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_required_env_var(char *content)
{
	if (ft_strncmp(content, "OLDPWD", 6) == 0
		|| ft_strncmp(content, "ZSH=", 4) == 0
		|| ft_strncmp(content,
			"VSCODE_GIT_ASKPASS_EXTRA_ARGS=", 29) == 0
		|| ft_strncmp(content, "VSCODE_GIT_ASKPASS_MAIN=", 24) == 0)
	{
		return (1);
	}
	return (0);
}

int	ft_check_env(t_list *env)
{
	int		len;
	int		i;
	t_list	*temp;
	char	*content;

	len = ft_lstsize(env);
	i = 1;
	if (len == 5)
	{
		temp = env;
		while (temp)
		{
			content = (char *)temp->content;
			if (is_required_env_var(content))
			{
				i++;
			}
			temp = temp->next;
		}
	}
	if (i == len)
	{
		return (1);
	}
	return (0);
}

t_list	*ft_init_pwd(void)
{
	t_list	*lst;
	char	cwd[1024];
	char	*dir;

	lst = NULL;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (NULL);
	dir = ft_strjoin("PWD=", cwd);
	if (!dir)
		return (NULL);
	ft_lstadd_back(&lst, ft_lstnew_index(dir, 1));
	return (lst);
}

int	ft_init_shlvl_and_underscore(t_list **lst)
{
	char	*shlvl;
	char	*underscore;

	shlvl = strdup("SHLVL=0");
	if (!shlvl)
		return (0);
	ft_lstadd_back(lst, ft_lstnew_index(shlvl, 1));
	underscore = ft_strdup("_=/usr/bin/env");
	if (!underscore)
	{
		free(shlvl);
		return (0);
	}
	ft_lstadd_back(lst, ft_lstnew_index(underscore, 1));
	return (1);
}

int	ft_init_oldpwd_and_path(t_list **lst)
{
	char	*oldpwd;
	char	*path;

	oldpwd = strdup("OLDPWD");
	if (!oldpwd)
		return (0);
	ft_lstadd_back(lst, ft_lstnew_index(oldpwd, 2));
	path = strdup("PATH=/Users/hel-band/goinfre/homebrew/bin:"
			"/usr/local/bin:/usr/bin:/bin:"
			"/usr/sbin:/sbin:/usr/local/munki:"
			"/Library/Apple/usr/bin");
	if (!path)
	{
		free(oldpwd);
		return (0);
	}
	ft_lstadd_back(lst, ft_lstnew_index(path, 0));
	return (1);
}
