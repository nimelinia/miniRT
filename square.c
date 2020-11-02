/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 18:15:43 by scopycat          #+#    #+#             */
/*   Updated: 2020/11/02 21:42:17 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

void		draw_square(t_scene *scene, t_mlx *mlx, int x, int i)
{
	t_index		sq;

	sq.i_f = 4;
	sq.i_f_n = i;
	sq.count = scene->square->count;
	draw_square_util(scene, mlx, x, sq);
}

void		draw_square_util(t_scene *scene, t_mlx *mlx, int x, t_index sq)
{
	int			y;
	int			i;
	t_square	*tmp_sq;

	tmp_sq = scene->square;
	i = sq.i_f_n;
	while (i--)
		tmp_sq = tmp_sq->next;
	while (x < scene->resol.x_size)
	{
		y = 0;
		while (y < scene->resol.y_size)
		{
			if ((sq.t = check_square(scene, x, y, sq.i_f_n)) &&
				sq.t <= scene->points[x][y])
			{
				sq.ind_l_n = 0;
				my_mlx_pixel_put(mlx, x, y, convert_colour(tmp_sq->colour, \
					find_colour_2(scene, x, y, sq)));
				scene->points[x][y] = sq.t;
			}
			y++;
		}
		x += 4;
	}
}

double		check_square(t_scene *scene, int x, int y, int i)
{
	t_xyzpoint	canvas;
	double		close_t;
	double		t;
	t_xyzpoint	ray;
	t_square	*sq;

	canvas = find_center_canvas(scene, x, y);
	close_t = MAXFLOAT;
	sq = scene->square;
	while (i--)
		sq = sq->next;
	sq->orient = normalize_orient(sq->center, sq->orient, \
		scene->camera->center);
	ray = substruct_vector(canvas, scene->camera->center);
	ray = normalize_vector(ray);
	t = (scalar(sq->center, sq->orient) - scalar(sq->orient,  \
		scene->camera->center)) / scalar(sq->orient, canvas);
	if (t >= 1 && t < close_t && check_inside_square(scene->camera->center, \
		sq, canvas, t))
		close_t = t;
	else
		return (0);
	return (close_t);
}

int			check_inside_square(t_xyzpoint cam, t_square *square, \
			t_xyzpoint ray, double t)
{
	t_angles	sq;
	double		diagonal;
	t_xyzpoint	point;

	sq.a = find_first_angle(square);
	diagonal = sqrt(2 * pow(square->lenght, 2));
	sq.c = find_point_coordinates(square->center, sq.a, -(diagonal / 2));
	sq.a = find_point_coordinates(square->center, sq.a, diagonal / 2);
	sq.b = substruct_vector(sq.a, square->center);
	sq.b = vector_mult(square->orient, sq.b);
	sq.b = normalize_vector(sq.b);
	sq.d = find_point_coordinates(square->center, sq.b, -(diagonal / 2));
	sq.b = find_point_coordinates(square->center, sq.b, diagonal / 2);
	if (scalar(ray, square->orient) < 0)
		ray = mult_num_vect(ray, -1);
	point = find_point_coordinates(cam, ray, t);
	if ((scalar(ray, vector_mult(substruct_vector(sq.b, sq.a), \
		substruct_vector(point, sq.a))) >= 0 && scalar(ray, \
		vector_mult(substruct_vector(sq.c, sq.b), substruct_vector(point, \
		sq.b))) >= 0 && scalar(ray, vector_mult(substruct_vector(sq.d, sq.c), \
		substruct_vector(point, sq.c))) >= 0 && scalar(ray, vector_mult(\
		substruct_vector(sq.a, sq.d), substruct_vector(point, sq.d))) >= 0))
		return (1);
	else
		return (0);
}

t_xyzpoint	find_first_angle(t_square *square)
{
	t_xyzpoint	vector;
	double		e;

	e = (scalar(square->center, square->orient));
	if (square->orient.x)
		vector = (t_xyzpoint){e / square->orient.x, 0, 0};
	else if (square->orient.y)
		vector = (t_xyzpoint){0, e / square->orient.y, 0};
	else
		vector = (t_xyzpoint){0, 0, e / square->orient.z};
	if (e == 0)
	{
		vector.x = square->orient.x == 0 ? 1 : square->orient.x;
		vector.y = square->orient.y == 0 ? 1 : square->orient.y;
		vector.z = square->orient.z == 0 ? 1 : square->orient.z;
	}
	vector = substruct_vector(square->center, vector);
	vector = normalize_vector(vector);
	return (vector);
}
