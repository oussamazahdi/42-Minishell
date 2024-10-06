/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:55:01 by ozahdi            #+#    #+#             */
/*   Updated: 2024/10/06 10:19:38 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void ft_print_token(t_token *token)
{
	while (token)
	{
		// printf("\x1b[38;5;214mtoken->content[%d] [%d] = %s\x1b[0m\n",token->type, token->flag ? "true" : fails ,token->content);
		printf("\x1b[38;5;214mtoken->content[%d] [%s] = %s\x1b[0m\n",token->type, token->flag ? "True" : "False" ,token->content);
		token = token->next;
	}
}

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













//  int g_xs = 0;
// static void	ft_readline_test(t_data **line, char **av, int ac)
// {
// 	char			*read;
// 	char			*new;
// 	struct termios	att;

// 	read = NULL;
// 	term_attr(&att);
// 	if (ac == 3)
// 	{
// 		new = ft_chifr(ft_strtrim(read, BLANK));
// 		free(read);
// 		new = ft_strdup(av[2]);
// 		if (!ft_parsing(line, new))
// 		{
// 			g_xs = 1;
// 			// printf("exit_code : [%d]\n", (*line)->exit_status);
// 			// printf("***************************************\n");
// 			exit (258);
// 			// printf("***************************************\n");
// 			return;
			
// 		}
// 		// {
// 			if (!ft_fill_token(line, new))
// 			{
// 				g_xs = 1;
// 				return ;
// 			}
// 			if (!herdoc(line))
// 			{
// 				g_xs = 1;	
// 				return ;
// 			}
// 			ft_fill_struct(line);
// 			ft_lexer(line);
// 			// printf("exit status pars : [%d]\n", (*line)->exit_status);
// 			// ft_print_token((*line)->pars_token);
// 			// printf("-----------------------------------------\n");
// 			execute(line);
// 			if (isatty(STDIN_FILENO) && tcsetattr(0, TCSANOW, &att))
// 				perror("termios");
// 			g_xs = 1;
// 			// if (!ft_exit(read, line))
// 			// 	return ;
// 		}
// 	// }
// 	// else
// 	// {
// 	// 	ft_free_all(line);
// 	// 	g_xs = 1;
// 	// 	return ;
// 	// }
// }


// int	main(int ac, char **av, char **env)
// {
// 	t_data		*line;

// 	if (!isatty(STDIN_FILENO))
// 		exit (1);
// 	(void)ac;
// 	// if (ac != 1)
// 	// 	return (printf("minishell: %s: No such file or directory\n", \
// 	// 		av[1]), 127);
// 	line = malloc(sizeof(t_data));
// 	if (!line)
// 		exit (1);
// 	ft_init_struct(&line);
// 	copy_env(&line->env, env, line);
// 	rl_catch_signals = 0;
// 	while (1)
// 	{
// 		ft_add_enver(line);
// 		signal(SIGQUIT, SIG_IGN);
// 		signal(SIGINT, handle_sigint);
// 		// ft_readline(&line);
// 		ft_readline_test(&line, av, ac);
// 		if (g_xs == 1)
// 			exit (line->exit_status);
// 	}
// }
