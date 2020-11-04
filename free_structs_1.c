/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:15:51 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/30 17:18:57 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

int		free_struct(t_scene *scene)
{
	(void)scene;
	free_camera(scene);
	free_light(scene);
	free_sphere(scene);
	free_plane(scene);
	free_triangle(scene);
	free_square(scene);
	free_cylin(scene);
	free_points(scene);
	exit(0);
}

void	free_camera(t_scene *scene)
{
	t_camera	*new;

	new = scene->camera;
	while (new)
	{
		scene->camera = scene->camera->next;
		free(new);
		new = scene->camera;
	}
}

void	free_light(t_scene *scene)
{
	t_light	*new;

	new = scene->light;
	while (new)
	{
		scene->light = scene->light->next;
		free(new);
		new = scene->light;
	}
}

void	free_sphere(t_scene *scene)
{
	t_sphere	*new;

	new = scene->sphere;
	while (new)
	{
		scene->sphere = scene->sphere->next;
		free(new);
		new = scene->sphere;
	}
}

void	free_plane(t_scene *scene)
{
	t_plane	*new;

	new = scene->plane;
	while (new)
	{
		scene->plane = scene->plane->next;
		free(new);
		new = scene->plane;
	}
}
