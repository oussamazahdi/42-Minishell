REDIRECT_DIR	=	src/redirect/
INIT_DIR		=	src/init_utils/
BUILT_DIR		=	src/builtins/
EXEC_DIR		=	src/exec/
FREE_DIR		=	src/free/
PARS_DIR		=	parsing/
CFLAGS			=	-Wall -Wextra -Werror
NAME			=	minishell
LIBFT_DIR		=	libft
LIBFT			=	$(LIBFT_DIR)/libft.a
LDFLAGS			=	-L/Users/$(USER)/.brew/opt/readline/lib
CPPFLAGS		=	-I/Users/$(USER)/.brew/opt/readline/include
CC				=	cc
F_LFT			=	-L$(LIBFT_DIR) -lft
INC				=	-I$(LIBFT_DIR)
INCLUDE			=	include/minishell.h
SRC				=	main.c $(PARS_DIR)ft_add_split_to_token.c $(PARS_DIR)ft_create_env.c\
					$(PARS_DIR)ft_expande_export.c $(PARS_DIR)ft_expande1.c $(PARS_DIR)ft_expande2.c\
					$(PARS_DIR)ft_change_exp.c $(PARS_DIR)signals2.c $(PARS_DIR)herdoc2.c\
					$(PARS_DIR)ft_expande3.c $(PARS_DIR)ft_fill_token.c $(PARS_DIR)ft_fill_token2.c\
					$(PARS_DIR)ft_fill_token3.c $(PARS_DIR)ft_fill_token4.c $(PARS_DIR)ft_parsing.c\
					$(PARS_DIR)ft_parsing2.c $(PARS_DIR)ft_protect_expand.c $(PARS_DIR)ft_quotes_remove.c\
					$(PARS_DIR)ft_split.c $(PARS_DIR)herdoc_expande.c $(PARS_DIR)herdoc.c\
					$(PARS_DIR)lexer.c $(PARS_DIR)lst_tools1.c $(PARS_DIR)signals.c\
					$(PARS_DIR)tools1.c $(PARS_DIR)tools2.c $(PARS_DIR)tools4.c $(PARS_DIR)tools5.c\
					$(PARS_DIR)tools3.c $(PARS_DIR)ft_normal_expande.c $(PARS_DIR)tools6.c \
					$(PARS_DIR)ft_clear_empty_nodes.c\
					$(INIT_DIR)init_utils.c $(BUILT_DIR)env_utils.c \
					$(BUILT_DIR)execute_builtin.c $(BUILT_DIR)exit.c \
					$(BUILT_DIR)env.c $(BUILT_DIR)pwd.c $(BUILT_DIR)unset.c \
					$(BUILT_DIR)handle_cd_with_args.c \
					$(BUILT_DIR)export.c $(BUILT_DIR)export_utils.c \
					$(BUILT_DIR)export_remove_process.c $(BUILT_DIR)echo.c \
					$(BUILT_DIR)cd.c $(BUILT_DIR)exit_utils.c $(EXEC_DIR)exec.c \
					$(BUILT_DIR)get_env_var_value.c \
					$(EXEC_DIR)child_process.c $(EXEC_DIR)finally_execute.c \
					$(EXEC_DIR)child_dups.c $(EXEC_DIR)pipes.c \
					$(EXEC_DIR)get_cmd_and_builtin.c $(EXEC_DIR)wait_all_process.c \
					$(EXEC_DIR)verify.c $(REDIRECT_DIR)files.c \
					$(REDIRECT_DIR)deal_with_fd.c $(FREE_DIR)free.c  $(FREE_DIR)ft_free_all.c\

OBJ				=	$(SRC:.c=.o)

all				: $(LIBFT) $(NAME) 

$(LIBFT)		:
				@$(MAKE) -C $(LIBFT_DIR)

%.o				: %.c $(INCLUDE)
				$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME)			: $(OBJ) 
				$(CC) $(OBJ) $(F_LFT) -lreadline $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $(NAME)

clean			:
				@make clean -C $(LIBFT_DIR)
				@rm -f $(OBJ)

fclean			:	clean
				@make fclean -C $(LIBFT_DIR)
				@rm -f $(NAME)

re				: fclean all

.PHONY			: all clean fclean re $(LIBFT)
