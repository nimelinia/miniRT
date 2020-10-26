/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:19:20 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/26 19:00:47 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

void	draw_sphere(t_scene *scene, t_mlx *mlx, int x, int i) // void *mlx_ptr, void *win_ptr)
{
	int		y;
	int		colour;
	// double	t[4];
	t_sphere	*tmp_sp;
	t_index		sp;

	y = 0;
	sp.ind_fig = 1;
	sp.ind_fig_n = i;
	sp.count = scene->sphere->count;
	// t[1] = 1;
	// t[2] = i;
	tmp_sp = scene->sphere;
	while (i--)
		tmp_sp = tmp_sp->next;
	while (x < scene->resol.x_size)
	{
		while (y < scene->resol.y_size)
		{
			if ((sp.t = check_sphere(scene, x, y, sp.ind_fig_n)) && sp.t <= scene->points[x][y])
			{
				sp.ind_l_n = 0;
				colour = convert_colour(tmp_sp->colour, find_colour(scene, x, y, sp));
				my_mlx_pixel_put(mlx, x, y, colour);
				//mlx_pixel_put(mlx_ptr, win_ptr, x, y, colour); //convert_colour(scene->sphere->colour, light));
				scene->points[x][y] = sp.t;
			}
			y++;
		}
		x += 4;
		y = 0;
	}
}

double		check_sphere(t_scene *scene, int x, int y, int i)
{
	double		t1;
	double		t2;
	double		close_t;
	t_xyzpoint	canvas;
	int			close_sp;

	canvas = find_center_canvas(scene, x, y); // canvas = normalize_vector(canvas); // не факт, что надо
	close_t = MAXFLOAT;
	close_sp = 0;
	t1 = find_first_t(scene, canvas, i);
	t2 = find_second_t(scene, canvas, i);
	if (t1 >= 1 && t1 < close_t)
	{
		close_t = t1;
		close_sp = scene->sphere->count;
	}
	if (t2 >= 1 && t2 < close_t)
	{
		close_t = t2;
		close_sp = scene->sphere->count;
	}
	if (!close_sp)
		return (0);
	else
		return (close_t);
}
