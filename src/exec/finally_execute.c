/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finally_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:00:12 by hel-band          #+#    #+#             */
/*   Updated: 2024/08/15 13:00:12 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**turn_env_to_arr(t_list *env)
{
	char	**arr;
	int		i;

	arr = ft_calloc(sizeof(char *), ft_lstsize(env) + 1);
	i = 0;
	while (env != NULL)
	{
		arr[i] = ft_calloc(sizeof(char), ft_strlen(env->content) + 1);
		ft_strlcpy(arr[i], env->content, ft_strlen(env->content) + 1);
		env = env->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**find_path(char **env)
{
	int		i;
	char	**temp;
	char	**paths;

	i = 0;
	while (env[i] != NULL && ft_strncmp("PATH=", env[i], 5) != 0)
		i++;
	if (env[i] == NULL)
		return (NULL);
	temp = ft_split(&env[i][5], ':');
	i = 0;
	while (temp[i] != NULL)
		i++;
	paths = ft_calloc(sizeof(char *), (i + 1));
	i = -1;
	while (temp[++i] != NULL)
		paths[i] = ft_strjoin(temp[i], "/");
	paths[i] = NULL;
	ft_free_str_arr(&temp);
	return (paths);
}

int	try_paths(t_exec *exec, char **path, char **env)
{
	int		i;
	int		strlen;
	char	*copy;

	if (verify(access(exec->cmd[0], F_OK), exec->cmd[0], exec->cmd, env) == 0)
		return (126);
	i = -1;
	if (path != NULL)
	{
		while (path[++i])
		{
			strlen = ft_strlen(path[i]) + ft_strlen(exec->cmd[0]) + 1;
			copy = ft_calloc(strlen, sizeof(char));
			ft_strlcat(copy, path[i], strlen);
			ft_strlcat(copy, exec->cmd[0], strlen);
			if (access(copy, F_OK) == 0)
			{
				verify_permission(copy, exec->cmd, env);
				return (free(copy), 126);
			}
			free(copy);
		}
	}
	return (127);
}

void	verify_permission(char *copy, char **cmd, char **env)
{
	if (access(copy, X_OK) == 0)
		execve(copy, cmd, env);
}

int	verify(int result, char *str, char **cmd, char **env)
{
	if (result == 0)
	{
		verify_permission(str, cmd, env);
		return (0);
	}
	return (-1);
}
