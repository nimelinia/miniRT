/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:19:20 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/30 13:44:04 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

void		draw_sphere(t_scene *scene, t_mlx *mlx, int x, int i)
{
	t_index		sp;

	sp.i_f = 1;
	sp.i_f_n = i;
	sp.count = scene->sphere->count;
	draw_sphere_util(scene, mlx, x, sp);
}

void		draw_sphere_util(t_scene *scene, t_mlx *mlx, int x, t_index sp)
{
	int			y;
	int			i;
	t_sphere	*tmp_sp;

	i = sp.i_f_n;
	tmp_sp = scene->sphere;
	while (i--)
		tmp_sp = tmp_sp->next;
	while (x < scene->resol.x_size)
	{
		y = 0;
		while (y < scene->resol.y_size)
		{
			if ((sp.t = check_sphere(scene, x, y, sp.i_f_n)) &&
				sp.t <= scene->points[x][y])
			{
				sp.ind_l_n = 0;
				my_mlx_pixel_put(mlx, x, y, convert_colour(tmp_sp->colour, \
					find_colour(scene, x, y, sp)));
				scene->points[x][y] = sp.t;
			}
			y++;
		}
		x += 4;
	}
}

double		check_sphere(t_scene *scene, int x, int y, int i)
{
	double		t1;
	double		t2;
	double		close_t;
	t_xyzpoint	canvas;
	int			close_sp;

	canvas = find_center_canvas(scene, x, y);
	close_t = MAXFLOAT;
	close_sp = 0;
	t1 = find_first_t(scene, canvas, i);
	t2 = find_second_t(scene, canvas, i);
	if (t1 >= 0.1 && t1 < close_t)
	{
		close_t = t1;
		close_sp = scene->sphere->count;
	}
	if (t2 >= 0.1 && t2 < close_t)
	{
		close_t = t2;
		close_sp = scene->sphere->count;
	}
	if (!close_sp)
		return (0);
	else
		return (close_t);
}
