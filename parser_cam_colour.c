/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cam_colour.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:49:09 by scopycat          #+#    #+#             */
/*   Updated: 2020/11/03 14:26:07 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "get_next_line.h"
#include "minilibx_mms/mlx.h"

int			pars_one_colour(char **line)
{
	int		colour;

	colour = 0;
	while (line && *line && ft_isdigit(**line))
	{
		colour = colour * 10 + **line - '0';
		(*line)++;
	}
	if (**line == ',')
		(*line)++;
	return (colour);
}

t_colour	pars_colour(char **line, t_scene *scene)
{
	t_colour	colour;

	colour.r_colour = pars_one_colour(line);
	if ((!line || !(*line) || !(ft_isdigit(**line))) && !(scene->mistake = 0))
		return (colour);
	colour.g_colour = pars_one_colour(line);
	if ((!line || !(*line) || !(ft_isdigit(**line))) && !(scene->mistake = 0))
		return (colour);
	colour.b_colour = pars_one_colour(line);
	if (colour.r_colour > 255 || colour.r_colour < 0 || colour.g_colour > 255 \
		|| colour.g_colour < 0 || colour.b_colour > 255 || colour.b_colour < 0)
		scene->mistake = 0;
	return (colour);
}

int			pars_camera_list(char *line, t_scene *scene)
{
	t_xyzpoint	vect;

	line++;
	while (line && *line == ' ')
		line++;
	scene->camera->center = pars_center(&line, scene);
	while (line && *line == ' ')
		line++;
	scene->camera->orient = normalize_vector(pars_orient(&line, scene));
	while (line && *line == ' ')
		line++;
	if (!scene->mistake || !line || !ft_isdigit(*line))
		return (write(2, "Error\nwrong camera\n", 19));
	scene->camera->fov = pars_one_colour(&line);
	if (scene->camera->fov >= 180)
		return (write(2, "Error\nwrong camera\n", 19));
	if (scene->camera->orient.x != 0 || scene->camera->orient.z != 0)
		vect = (t_xyzpoint) {0, 1, 0};
	else
		vect = (t_xyzpoint) {1, 0, 0};
	scene->camera->ox = normalize_vector(vector_mult(scene->camera->orient, \
		vect));
	scene->camera->oy = normalize_vector(vector_mult(scene->camera->ox, \
		scene->camera->orient));
	return (0);
}

int			pars_camera(char *line, t_scene *scene)
{
	static int	count_camera = 0;
	t_camera	*new;

	if (count_camera == 0)
	{
		count_camera = 1;
		scene->camera->count++;
		return (pars_camera_list(line, scene));
	}
	else
	{
		count_camera = 0;
		new = c_init();
		new->next = scene->camera;
		scene->camera = new;
		return (pars_camera(line, scene));
	}
}
