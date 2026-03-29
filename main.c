/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:55:01 by ozahdi            #+#    #+#             */
/*   Updated: 2024/10/06 15:35:02 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static void	ft_init_struct(t_data **line)
{
	(*line)->last_command = ft_strdup("mini");
	(*line)->lexer = NULL;
	(*line)->env = NULL;
	(*line)->env_pars = NULL;
	(*line)->token = NULL;
	(*line)->pars_token = NULL;
	(*line)->has_builtin = 0;
	(*line)->process_count = 1;
	(*line)->builtin_check = 0;
	(*line)->exit_status = 0;
	(*line)->home = NULL;
}

static void	term_attr(struct termios *att)
{
	if (isatty(STDIN_FILENO) && tcgetattr(STDIN_FILENO, att))
		perror("termios");
}

static void	ft_readline(t_data **line)
{
	char			*read;
	char			*new;
	struct termios	att;

	read = NULL;
	term_attr(&att);
	read = readline("➜ Minishell $ ");
	if (!ft_exit(read, line))
		return ;
	new = ft_chifr(ft_strtrim(read, BLANK));
	free(read);
	if (ft_parsing(line, new))
	{
		if (!ft_fill_token(line, new))
			return ;
		if (!herdoc(line))
			return ;
		ft_fill_struct(line);
		ft_lexer(line);
		execute(line);
		if (isatty(STDIN_FILENO) && tcsetattr(0, TCSANOW, &att))
			perror("termios");
	}
	ft_free_all(line);
}

int	main(int ac, char **av, char **env)
{
	t_data		*line;

	if (!isatty(STDIN_FILENO))
		exit (1);
	if (ac != 1)
		return (printf("minishell: %s: No such file or directory\n", \
			av[1]), 127);
	line = malloc(sizeof(t_data));
	if (!line)
		exit (1);
	ft_init_struct(&line);
	copy_env(&line->env, env, line);
	rl_catch_signals = 0;
	while (1)
	{
		ft_add_enver(line);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_sigint);
		ft_readline(&line);
	}
}
