/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 18:15:43 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/26 19:01:15 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

void	draw_square(t_scene *scene, t_mlx *mlx, int x, int i) //void *mlx_ptr, void *win_ptr) //допилить свет и тени
{
	int		y;
	int		colour;
	// double	t[2];
	t_index		sq;
	t_square	*tmp_sq;

	y = 0;
	sq.ind_fig = 4;
	sq.ind_fig_n = i;
	sq.count = scene->square->count;
	tmp_sq = scene->square;
	while (i--)
		tmp_sq = tmp_sq->next;
	while (x < scene->resol.x_size)
	{
		while (y < scene->resol.y_size)
		{
			if ((sq.t = check_square(scene, x, y, sq.ind_fig_n)) && sq.t <= scene->points[x][y])
			{
				sq.ind_l_n = 0;
				colour = convert_colour(tmp_sq->colour, find_colour_2(scene, x, y, sq)); //find_colour_3(scene, x, y, t)); // тут пока без света - только рассеянный и без теней
				my_mlx_pixel_put(mlx, x, y, colour);
				// mlx_pixel_put(mlx_ptr, win_ptr, x, y, colour); //convert_colour(scene->sphere->colour, light));
				scene->points[x][y] = sq.t;
			}
			y++;
		}
		x += 4;
		y = 0;
	}
}

double	check_square(t_scene *scene, int x, int y, int i) // лажает на нормалях 1,0,0 0,1,0 и 0,0,1
{
	t_xyzpoint	canvas;
	double		close_t;
	double		t;
	t_xyzpoint	ray; // направление взгляда из камеры на точку на холсте
	t_square	*sq;

	canvas = find_center_canvas(scene, x, y);
	close_t = MAXFLOAT;
	sq = scene->square;
	while (i--)
		sq = sq->next;
   	sq->orient = normalize_orient(sq->center, sq->orient, scene->camera->center);
	ray = substruct_vector(canvas, scene->camera->center);
	ray = normalize_vector(ray);
	t = (scalar(sq->center, sq->orient) - scalar(sq->orient,  \
		scene->camera->center)) / scalar(sq->orient, ray);
	// t = length_to_pl_point(scene->camera->center, sq->orient, sq->center, ray);
	if (t >= 1 && t < close_t && check_inside_square(scene->camera->center, sq, ray, t))
		close_t = t;
	else
		return (0);	
	return (close_t);	
}

int		check_inside_square(t_xyzpoint cam, t_square *square, t_xyzpoint ray, double t) // разбить на подфункции - слишком много переменных
{
	t_xyzpoint	a;
	t_xyzpoint	b;
	t_xyzpoint	c;
	t_xyzpoint	d;
	double		e;
	double		diagonal;
	t_xyzpoint	point;

    // square->orient = normalize_vector(square->orient);
    e = (scalar(square->center, square->orient)); // нахожу D из уравнения плоскости Ax + By + Cz + D = 0 (по факту это -D)
	if (square->orient.x)
	{
		a.x =  e / square->orient.x;
		a.y = 0;
		a.z = 0;
	}
	else if (square->orient.y)
	{
		a.y =  e / square->orient.y;
		a.x = 0;
		a.z = 0;
	}
	else
	{
		a.z =  e / square->orient.z;
		a.x = 0;
		a.y = 0;
	}
	a = substruct_vector(square->center, a); // вектор из точки пересечения в центр квадрата
	a = normalize_vector(a);
	diagonal = sqrt(2 * pow(square->lenght, 2));
	c = find_point_coordinates(square->center, a, -(diagonal / 2));
	a = find_point_coordinates(square->center, a, diagonal / 2);
	b = substruct_vector(a, square->center); //(нахожу вектор из центра квадрата в первую вершину)
	b = vector_mult(square->orient, b);
	b = normalize_vector(b);
	d = find_point_coordinates(square->center, b, -(diagonal / 2));
	b = find_point_coordinates(square->center, b, diagonal / 2);
	if (scalar (ray, square->orient) < 0)
		ray = mult_num_vect(ray, -1);
    point = find_point_coordinates(cam, ray, t);
	// if ((scalar(vector_mult(substruct_vector(b, a), substruct_vector(point, a)), vector_mult(substruct_vector(c, b), substruct_vector(point, b))) > 0 &&
	//  	scalar(vector_mult(substruct_vector(c, b), substruct_vector(point, b)), vector_mult(substruct_vector(d, c), substruct_vector(point, c))) > 0 &&
	// 	scalar(vector_mult(substruct_vector(d, c), substruct_vector(point, c)), vector_mult(substruct_vector(a, d), substruct_vector(point, d))) > 0 &&
	// 	scalar(vector_mult(substruct_vector(a, d), substruct_vector(point, d)), vector_mult(substruct_vector(b, a), substruct_vector(point, a))) > 0))
	// 	return (1);
	if ((scalar(ray, vector_mult(substruct_vector(b, a), substruct_vector(point, a))) >= 0 &&
	 	scalar(ray, vector_mult(substruct_vector(c, b), substruct_vector(point, b))) >= 0 &&
		scalar(ray, vector_mult(substruct_vector(d, c), substruct_vector(point, c))) >= 0 &&
		scalar(ray, vector_mult(substruct_vector(a, d), substruct_vector(point, d))) >= 0))
		return (1);
	else
		return (0);
}