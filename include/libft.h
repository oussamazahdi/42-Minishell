/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahdi <ozahdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:05:45 by hel-band          #+#    #+#             */
/*   Updated: 2024/10/06 12:00:02 by ozahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

typedef struct s_list
{
	char			*content;
	char			*name;
	char			*value;
	int				type;
	int				index;
	struct s_list	*next;
}		t_list;

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_strdigit(char *str);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_strlen(char *s);
int			ft_arrsize(char **arr);
void		*ft_memset(void *s, int c, int n);
void		ft_bzero(void *s, int n);
void		*ft_memcpy(void *dest, void *src, int n);
void		*ft_memmove(void *dest, void *src, int n);
int			ft_strlcpy(char *dst, char *src, int size);
int			ft_strlcat(char *dest, char *src, int size);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr( char *s, int c);
char		*ft_strrchr( char *s, int c);
int			ft_strcmp( char *s1, char *s2);
int			ft_strncmp( char *s1, char *s2, int n);
void		*ft_memchr( void *s, int c, int n);
int			ft_memcmp( void *s1, void *s2, int n);
char		*ft_strnstr( char *big, char *little, int len);
int			ft_atoi(char *nptr);
long		ft_atol(char *nptr);
void		*ft_calloc(int nmemb, int size);

// Part 2 functions
char		*ft_strdup(char *s);
char		*ft_substr(char *s, int start, int len);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strtrim(char *s1, char *set);
char		**ft_split(char *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
int			ft_putchar_fd(char c, int fd);
int			ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

// My functions
void		ft_free_str_arr(char ***arr);
int			ft_list_len(t_list *lst);
void		ft_swap_lst(t_list *lst);

//ft_printf_fd
int			ft_printf_fd(int fd, char *str, ...);

/* Bonus part */
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstiter(t_list *lst, void (*f)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
