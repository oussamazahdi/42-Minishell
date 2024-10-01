/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normal_expande.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:59:49 by ozahdi            #+#    #+#             */
/*   Updated: 2024/09/30 15:36:17 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	extract_expansion_components(char *ptr, char **befor, \
	char **expande, char **after)
{
	int		x;
	int		j;

	x = 0;
	while (ptr[x] && ptr[x] != '$')
		(x)++;
	if (ptr[x] && ptr[x] == '$' && (ptr[x + 1] == ' ' || !ptr[x + 1]))
		ptr[x++] *= -1;
	*befor = ft_substr(ptr, 0, x);
	x++;
	j = x;
	while (ptr[x] && (ft_isalnum(ptr[x]) || ptr[x] == '_' || ptr[x] == '?'))
		x++;
	*expande = ft_substr(ptr, j, x - j);
	*after = ft_substr(ptr, x, ft_strlen(ptr) - x);
	return (x);
}

static char	*perform_expansion(char *befor, char *expande, \
	char *after, t_data **line)
{
	char		*expanded_str;
	char		*result;
	t_token		*env;

	env = (*line)->env_pars;
	if (expande[0] == '?')
		expanded_str = ft_itoa((*line)->exit_status);
	else
		expanded_str = ft_change(expande, env, NULL, *line);
	if (expanded_str)
	{
		result = ft_strjoin_pars(befor, expanded_str);
		result = ft_strjoin_pars(result, after);
	}
	else
		result = ft_strjoin_pars(befor, after);
	if (expanded_str)
		free(expanded_str);
	return (result);
}

char	*ft_normal_expand(char *ptr, t_data **line)
{
	char		*befor;
	char		*expande;
	char		*after;
	int			i;

	if (!ptr)
		return (NULL);
	ptr = ft_convert_negatives(ptr);
	while (ft_check_expande(ptr))
	{
		i = 0;
		i = extract_expansion_components(ptr, &befor, &expande, &after);
		free(ptr);
		ptr = perform_expansion(befor, expande, after, line);
		if (expande)
			free(expande);
		if (after)
			free(after);
	}
	return (ft_convert_negatives(ptr));
}
