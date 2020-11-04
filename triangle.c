/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:46:56 by scopycat          #+#    #+#             */
/*   Updated: 2020/11/03 13:32:01 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

void	draw_triangle(t_scene *scene, t_mlx *mlx, int x, int i)
{
	t_index		tr;

	tr.i_f = 3;
	tr.i_f_n = i;
	tr.count = scene->triangle->count;
	draw_triangle_util(scene, mlx, x, tr);
}

void	draw_triangle_util(t_scene *scene, t_mlx *mlx, int x, t_index tr)
{
	int			y;
	int			i;
	t_triangle	*tmp_tr;

	i = tr.i_f_n;
	tmp_tr = scene->triangle;
	while (i--)
		tmp_tr = tmp_tr->next;
	while (x < scene->resol.x_size)
	{
		y = 0;
		while (y < scene->resol.y_size)
		{
			if ((tr.t = check_triangle(scene, x, y, tr.i_f_n)) &&
				tr.t <= scene->points[x][y])
			{
				tr.ind_l_n = 0;
				my_mlx_pixel_put(mlx, x, y, convert_colour(tmp_tr->colour, \
					find_colour_2(scene, x, y, tr)));
				scene->points[x][y] = tr.t;
			}
			y++;
		}
		x += 4;
	}
}

double	check_triangle(t_scene *scene, int x, int y, int i)
{
	t_xyzpoint	canvas;
	double		t;
	t_triangle	*tr;
	t_xyzpoint	normal;

	canvas = find_center_canvas(scene, x, y);
	tr = scene->triangle;
	while (i--)
		tr = tr->next;
	normal = vector_mult(substruct_vector(tr->angle_two, \
		tr->angle_one), substruct_vector(tr->angle_three, tr->angle_one));
	normal = normalize_orient(tr->angle_one, normal, \
		scene->camera->center);
	t = find_t_triangle(scene, canvas, tr, normal);
	if (t >= 0.1 && t < MAXFLOAT && check_inside_triangle(\
		scene->camera->center, tr, canvas, t))
		return (t);
	else
		return (0);
}

double	find_t_triangle(t_scene *scene, t_xyzpoint canvas, t_triangle *tr,\
			t_xyzpoint normal)
{
	double		t;
	t_xyzpoint	point;

	point = (t_xyzpoint){0, 0, 0};
	if (scalar(normal, tr->angle_one))
		t = length_to_pl_point(scene->camera->center, normal, \
			tr->angle_one, canvas);
	else if (scalar(normal, tr->angle_two))
		t = length_to_pl_point(scene->camera->center, normal, \
			tr->angle_two, canvas);
	else
		t = length_to_pl_point(scene->camera->center, normal, \
			tr->angle_three, canvas);
	return (t);
}

int		check_inside_triangle(t_xyzpoint cam, t_triangle *triangle, \
			t_xyzpoint ray, double t)
{
	t_xyzpoint	a;
	t_xyzpoint	b;
	t_xyzpoint	c;
	t_xyzpoint	point;

	a = substruct_vector(triangle->angle_one, \
		triangle->angle_two);
	b = substruct_vector(triangle->angle_two, \
		triangle->angle_three);
	c = substruct_vector(triangle->angle_three, \
		triangle->angle_one);
	point = find_point_coordinates(cam, ray, t);
	if (scalar(vector_mult(a, substruct_vector(point, \
		triangle->angle_one)), vector_mult(b, substruct_vector(point, \
		triangle->angle_two))) > 0. && \
		scalar(vector_mult(b, substruct_vector(point, \
		triangle->angle_two)), vector_mult(c, substruct_vector(point, \
		triangle->angle_three))) > 0. && \
		scalar(vector_mult(a, substruct_vector(point, \
		triangle->angle_one)), vector_mult(c, substruct_vector(point, \
		triangle->angle_three))) > 0.)
		return (1);
	else
		return (0);
}
