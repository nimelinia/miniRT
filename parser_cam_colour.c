/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cam_colour.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:49:09 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/19 23:07:30 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft/libft.h"
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
	line++;
	while (line && *line == ' ')
		line++;
	scene->camera->center = pars_center(&line, scene);
	while (line && *line == ' ')
		line++;
	scene->camera->orient = pars_orient(&line, scene);
	while (line && *line == ' ')
		line++;
	if (!scene->mistake || !line || !ft_isdigit(*line))
		return (write(2, "Error\nwrong camera\n", 19));
	scene->camera->fov = pars_one_colour(&line);
	if (scene->camera->fov >= 180)
		return (write(2, "Error\nwrong camera\n", 19));
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
