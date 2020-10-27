/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_multithread.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 21:16:33 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/27 10:30:28 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

void	prerender(t_scene *scene, t_mlx *mlx)
{
	int			x[4];
	pthread_t	thr_1;
	pthread_t	thr_2;
	pthread_t	thr_3;
	pthread_t	thr_4;
	
	(void)scene;
	(void)mlx;
	x[0] = 0;
	x[1] = 1;
	x[2] = 2;
	x[3] = 3;
	pthread_create(&thr_1, NULL, render, &x[0]);
	pthread_create(&thr_2, NULL, render, &x[1]);
	pthread_create(&thr_3, NULL, render, &x[2]);
	pthread_create(&thr_4, NULL, render, &x[3]);
	pthread_join(thr_1, NULL);
	pthread_join(thr_2, NULL);
	pthread_join(thr_3, NULL);
	pthread_join(thr_4, NULL);
}

void	*render(void *x)
{
	t_mlx		*mlx;
	t_scene		*scene;
	
	scene = g_scene; //copy_struct(g_scene); // тут по сути надо скопировать, а не приравнять
	mlx = &g_mlx;
	// scene->camera->orient = normalize_vector(scene->camera->orient);
	// check_cam(scene); // меняются координаты и в g_scene - нужно сделать копию, а не приравнять указатели
	render_threads(scene, mlx, *(int*)x);
	pthread_exit(NULL);
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
