# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/31 13:59:17 by hel-band          #+#    #+#              #
#    Updated: 2024/10/06 15:34:06 by ozahdi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = ft_atoi.c ft_isdigit.c ft_memset.c ft_strlcpy.c ft_tolower.c ft_bzero.c ft_isprint.c \
       ft_strchr.c ft_strlen.c ft_toupper.c ft_isalnum.c ft_memchr.c ft_strncmp.c ft_calloc.c \
       ft_isalpha.c ft_memcpy.c ft_strdup.c ft_strnstr.c ft_isascii.c ft_memmove.c ft_strlcat.c \
       ft_strrchr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c \
       ft_putendl_fd.c ft_putnbr_fd.c ft_strmapi.c ft_striteri.c ft_substr.c ft_memcmp.c ft_printf_fd.c \
	   ft_atol.c ft_arrsize.c ft_list_len.c ft_lstadd_back_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c\
	   ft_lstmap_bonus.c ft_lstsize_bonus.c ft_lstadd_front_bonus.c ft_lstdelone_bonus.c ft_lstlast_bonus.c\
	   ft_lstnew_bonus.c ft_free_str_arr.c ft_strdigit.c ft_swap_lst.c ft_strcmp.c \

OBJS = $(SRCS:.c=.o)

LIBC = ar rcs

NAME = libft.a

RM = rm -f

all: $(NAME)

$(NAME)		: $(OBJS) ../include/libft.h
			$(LIBC) $(NAME) $(OBJS)


%.o: %.c ../include/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re

