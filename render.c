/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 21:15:42 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/26 20:17:04 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

void	prerender(t_scene *scene, t_mlx *mlx)
{
	int			x[4];
	
	(void)scene;
	(void)mlx;
	// g_mlx = mlx;
	// g_scene = scene;
	x[0] = 0;
	x[1] = 1;
	x[2] = 2;
	x[3] = 3;
	render(&x[0]);
    render(&x[1]);
    render(&x[2]);
    render(&x[3]);
}

// void	render(t_scene *scene, t_mlx *mlx) // void *mlx_ptr, void *win_ptr)
void	*render(void *x)
{
	t_mlx		*mlx;
	t_scene		*scene;
	
	// scene = g_scene;
	scene = g_scene_copy;
	mlx = &g_mlx;
	render_threads(scene, mlx, *(int*)x);
	return (NULL);
}

void		render_threads(t_scene *scene, t_mlx *mlx, int x)
{
	int			i;
	int			count;

	i = 0;
	count = scene->sphere->count;
	while (count--) // tmp_sphere) // переделать на переключение камер
		draw_sphere(scene, mlx, x, i++); // mlx_ptr, win_ptr);
	i = 0;
	count = scene->plane->count;
	while (count--) //tmp_plane)
		draw_plane(scene, mlx, x, i++); //mlx_ptr, win_ptr);
	i = 0;
	count = scene->triangle->count;
	while (count--) //tmp_triangle)
		draw_triangle(scene, mlx, x, i++); //mlx_ptr, win_ptr);
	i = 0;
	count = scene->square->count;
	while (count--)
		draw_square(scene, mlx, x, i++);
	i = 0;
	count = scene->cylin->count;
	while (count--)
		draw_cylin(scene, mlx, x, i++);
}