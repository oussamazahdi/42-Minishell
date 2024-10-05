/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:15:55 by hel-band          #+#    #+#             */
/*   Updated: 2024/08/31 17:15:55 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int		ft_isspace(int c);

bool	is_quiet_mode(t_data *data)
{
	return (data->process_count > 1);
}

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f')
		return (c);
	return (0);
}

static bool	check_overflow(char *str, int sign)
{
	int		len;

	len = ft_strlen(str);
	if (len > 19)
		return (true);
	if (len == 19 && sign == -1
		&&ft_strncmp(str, "9223372036854775808", 19) > 0)
		return (true);
	if (len == 19 && sign == 1
		&&ft_strncmp(str, "9223372036854775807", 19) > 0)
		return (true);
	return (false);
}

static long long	ft_atoi_long(char *str, bool *error)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	*error = false;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (check_overflow(str, sign))
		return (*error = true, 0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (*error = true, 0);
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}

int	get_exit_code(char *arg, bool *error)
{
	unsigned long long		i;

	i = 0;
	if (!arg)
		return (2);
	while (ft_isspace(arg[i]) || (arg[i] == '+' && (arg[i + 1] == ' ' || \
		arg[i + 1] == '\0')) || (arg[i] == '-' && (arg[i + 1] == ' ' || \
		arg[i + 1] == '\0')))
		i++;
	if (i != 0)
		return (*error = true, 2);
	if (arg[i] == '\0')
		*error = true;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!ft_isdigit(arg[i]))
		*error = true;
	while (arg[i])
	{
		if (!(ft_isdigit(arg[i]) || ft_isspace(arg[i])))
			*error = true;
		i++;
	}
	return (ft_atoi_long(arg, error) % 256);
}
