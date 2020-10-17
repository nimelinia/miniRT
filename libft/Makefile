# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scopycat <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/05 13:34:10 by scopycat          #+#    #+#              #
#    Updated: 2020/05/14 18:41:10 by scopycat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAG = -c -Wall -Wextra -Werror

NAME = libft.a

FUNC = ft_atoi.c\
ft_bzero.c\
ft_calloc.c\
ft_isalnum.c\
ft_isalpha.c\
ft_isascii.c\
ft_isdigit.c\
ft_isprint.c\
ft_itoa.c\
ft_memccpy.c\
ft_memchr.c\
ft_memcmp.c\
ft_memcpy.c\
ft_memmove.c\
ft_memset.c\
ft_putchar_fd.c\
ft_putendl_fd.c\
ft_putnbr_fd.c\
ft_putstr_fd.c\
ft_split.c\
ft_strlen.c\
ft_strlcpy.c\
ft_strlcat.c\
ft_strjoin.c\
ft_strdup.c\
ft_strchr.c\
ft_strmapi.c\
ft_strncmp.c\
ft_strnstr.c\
ft_strrchr.c\
ft_strtrim.c\
ft_substr.c\
ft_tolower.c\
ft_toupper.c\

OBJ = $(FUNC:.c=.o)

HEADER = libft.h

F_BONUS = ft_lstnew.c\
ft_lstadd_front.c\
ft_lstsize.c\
ft_lstlast.c\
ft_lstadd_back.c\
ft_lstdelone.c\
ft_lstclear.c\
ft_lstiter.c\
ft_lstmap.c\

O_BONUS = $(F_BONUS:.c=.o)

.PHONY: all clean fclean re bonus

all: $(NAME)

%.o: %.c $(HEADER)
	gcc $(FLAG)  -c $< -o $@

$(NAME): $(OBJ)
	ar -rc $(NAME) $(OBJ)
	ranlib $(NAME)

bonus: $(OBJ) $(O_BONUS)
	ar -rc $(NAME) $(OBJ) $(O_BONUS)

clean:
	rm -f $(OBJ) $(O_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all
