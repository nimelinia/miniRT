# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scopycat <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/13 20:15:44 by scopycat          #+#    #+#              #
#    Updated: 2020/10/13 18:16:07 by scopycat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



FLAG = -g -Wall -Wextra -Werror

NAME = libminirt.a

FUNC = minirt.c\
work_with_mlx.c\
cylinder.c\
cylinder_points.c\
cylinder_utils.c\
formules_vector.c\
get_next_line.c\
get_next_line_utils.c\
init_structure_1.c\
init_structure_2.c\
init_structure_3.c\
parser.c\
parser_cam_colour.c\
parser_cylin_plane.c\
parser_light_resol.c\
parser_sph_sq.c\
parser_triangle.c\
plane.c\
sphere.c\
sphere_utils.c\
square.c\
triangle.c

OBJ = $(FUNC:.c=.o)

HEADER = minirt.h

MLX = ./minilibx_mms

.PHONY: all clean fclean re bonus

all: $(NAME)

%.o: %.c $(HEADER)
	gcc $(FLAG) -c $< -o $@

$(NAME): $(OBJ)
	@make -C $(MLX)
	@cp $(MLX)/libmlx.dylib .
	ar -rc $(NAME) $(OBJ)
	gcc $(FUNC) -L. -lminirt -L$(MLX) -lmlx $(FLAG) -I $(MLX) -I $(HEADER) -o miniRT 
	ranlib $(NAME)

bonus: $(OBJ) $(O_BONUS)
	ar -rc $(NAME) $(OBJ) $(O_BONUS)

clean:
	@make clean -C $(MLX)
	rm -f $(OBJ) $(O_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all
