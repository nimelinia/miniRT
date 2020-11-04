/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_bonuses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:42:07 by scopycat          #+#    #+#             */
/*   Updated: 2020/11/03 15:24:51 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

int		mouse_pressed(t_scene *scene)
{
	(void)scene;
	// if (g_scene->camera->next)
	// 	g_scene->camera = g_scene->camera->next;
	// else if (g_scene->camera == g_camera)
	// 	return (0);
	// else
	// 	g_scene->camera = g_camera;
	// reinit_points(g_scene);
	// mlx_destroy_image(g_mlx.m_ptr, g_mlx.img);
	// g_mlx.img = mlx_new_image(g_mlx.m_ptr, scene->resol.x_size, \
	// 	scene->resol.y_size);
	// g_mlx.addr = mlx_get_data_addr(g_mlx.img, &g_mlx.bpp, \
	// 	&g_mlx.length, &g_mlx.end);
	// prerender(scene, &g_mlx);
	// mlx_put_image_to_window(g_mlx.m_ptr, g_mlx.w_ptr, g_mlx.img, 0, 0);
	return (0);
}

void	rotate_cam(t_scene *scene)
{
	t_xyzpoint	vect;

	if (g_scene->camera->ox.x == g_ox.x && g_scene->camera->oy.x == g_oy.x &&
		g_scene->camera->ox.y == g_ox.y && g_scene->camera->oy.y == g_oy.y &&
		g_scene->camera->ox.z == g_ox.z && g_scene->camera->oy.z == g_oy.z)
	{
		if (g_scene->camera->orient.x != 0 || g_scene->camera->orient.z != 0)
			vect = (t_xyzpoint) {0, -1, 0};
		else
			vect = (t_xyzpoint) {-1, 0, 0};
		g_scene->camera->ox = normalize_vector(vector_mult(\
			g_scene->camera->orient, vect));
		g_scene->camera->oy = normalize_vector(vector_mult(\
			g_scene->camera->ox, g_scene->camera->orient));
	}
	else
	{
		g_scene->camera->ox = g_ox;
		g_scene->camera->oy = g_oy;
	}
	redraw_pic(scene);
}

void	change_colours(t_scene *scene, int keycode)
{
	change_colours_figures(scene, keycode);
	redraw_pic(scene);
}

void	change_colours_figures(t_scene *scene, int keycode)
{
	change_colours_sphere(scene, keycode);
	change_colours_plane(scene, keycode);
	change_colours_triangle(scene, keycode);
	change_colours_square(scene, keycode);
	change_colours_cylin(scene, keycode);
}

void	redraw_pic(t_scene *scene)
{
	reinit_points(g_scene);
	mlx_destroy_image(g_mlx.m_ptr, g_mlx.img);
	g_mlx.img = mlx_new_image(g_mlx.m_ptr, g_scene->resol.x_size, \
		g_scene->resol.y_size);
	g_mlx.addr = mlx_get_data_addr(g_mlx.img, &g_mlx.bpp, \
		&g_mlx.length, &g_mlx.end);
	prerender(scene, &g_mlx);
	mlx_put_image_to_window(g_mlx.m_ptr, g_mlx.w_ptr, g_mlx.img, 0, 0);
}
