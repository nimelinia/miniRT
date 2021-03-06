# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/13 20:15:44 by scopycat          #+#    #+#              #
#    Updated: 2020/11/03 15:18:24 by scopycat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



FLAG = -g -Wall -Wextra -Werror

NAME = libminirt.a

FUNC = minirt.c\
work_with_mlx.c\
change_colours.c\
colour.c\
cylinder.c\
cylinder_points.c\
cylinder_utils.c\
find_figure_point.c\
formules_points.c\
formules_vector.c\
formules_vector_2.c\
free_structs_1.c\
free_structs_2.c\
get_next_line.c\
get_next_line_utils.c\
init_structure_1.c\
init_structure_2.c\
init_structure_3.c\
libfunc.c\
light.c\
parser.c\
parser_cam_colour.c\
parser_cylin_plane.c\
parser_light_resol.c\
parser_sph_sq.c\
parser_triangle.c\
plane.c\
save_bmp.c\
shadows.c\
some_bonuses.c\
sphere.c\
sphere_utils.c\
square.c\
triangle.c

RENDER = render.c

BONUS = render_multithread.c

OBJ_REND = $(FUNC:.c=.o)

OBJ = $(FUNC:.c=.o)

O_BONUS = $(BONUS:.c=.o)

HEADER = minirt.h

MLX = ./minilibx_mms

.PHONY: all clean fclean re bonus

all: $(NAME)

%.o: %.c $(HEADER)
	gcc $(FLAG) -c $< -o $@

$(NAME): $(OBJ) $(OBJ_REND)
	@make -C $(MLX)
	@cp $(MLX)/libmlx.dylib .
	ar -rc $(NAME) $(OBJ) $(OBJ_REND)
	gcc $(FUNC) $(RENDER) -L. -lminirt -L$(MLX) -lmlx $(FLAG) -I $(MLX) -I $(HEADER) -o miniRT 
	ranlib $(NAME)

bonus: $(OBJ) $(O_BONUS)
	@make -C $(MLX)
	@cp $(MLX)/libmlx.dylib .
	ar -rc $(NAME) $(OBJ) $(O_BONUS)
	gcc $(FUNC) $(BONUS) -L. -lminirt -L$(MLX) -lmlx $(FLAG) -O3 -I $(MLX) -I $(HEADER) -o miniRT 
	ranlib $(NAME)


clean:
	@make clean -C $(MLX)
	rm -f $(OBJ) $(O_BONUS) $(OBJ_REND)

fclean: clean
	rm -f $(NAME)

re: fclean all
