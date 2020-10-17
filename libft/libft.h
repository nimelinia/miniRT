/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 13:19:17 by scopycat          #+#    #+#             */
/*   Updated: 2020/05/10 20:35:58 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_atoi(char *str);
void				*ft_calloc(size_t num, size_t size);
void				ft_bzero(void *src, size_t num);
int					ft_isalnum(int sym);
int					ft_isalpha(int sym);
int					ft_isascii(int sym);
int					ft_isprint(int sym);
int					ft_isdigit(int sym);
char				*ft_itoa(int n);
void				*ft_memccpy(void *dst, const void *src,
							int s, size_t count);
void				*ft_memchr(const void *src, int s, size_t count);
int					ft_memcmp(const void *s1, const void *s2, size_t count);
void				*ft_memcpy(void *dst, const void *src, size_t count);
void				*ft_memmove(void *dst, const void *src, size_t count);
void				*ft_memset(void *src, int v, size_t num);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int nb, int fd);
void				ft_putstr_fd(char *s, int fd);
size_t				ft_strlen(const char *str);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strdup(const char *str);
char				*ft_strchr(const char *str, int sym);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *str1, const char *str2, size_t len);
char				*ft_strnstr(const char *big, const char *small, size_t len);
char				*ft_strrchr(const char *str, int sym);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_tolower(int sym);
int					ft_toupper(int sym);
char				**ft_split(char const *s, char c);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

#endif
