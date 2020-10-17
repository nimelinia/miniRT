/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:42:55 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/09 15:04:03 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft/libft.h"
#include "get_next_line.h"
#include "minilibx_mms/mlx.h"

t_xyzpoint	pars_orient(char **line, t_scene *scene)
{
	t_xyzpoint	orient;

	if ((!line || !(*line) || (!(ft_isdigit(**line)) && !(**line == '-')))
		&& !(scene->mistake = 0))
		return (init_orient());
	orient.x = pars_double(0, line);
	if (**line != ',' && !(scene->mistake = 0))
		return (orient);
	(*line)++;
	if ((!line || !(*line) || (!(ft_isdigit(**line)) && !(**line == '-')))
		&& !(scene->mistake = 0))
		return (orient);
	orient.y = pars_double(0, line);
	if (**line != ',' && !(scene->mistake = 0))
		return (orient);
	(*line)++;
	if ((!line || !(*line) || (!(ft_isdigit(**line)) && !(**line == '-')))
		&& !(scene->mistake = 0))
		return (orient);
	orient.z = pars_double(0, line);
	if (orient.x < -1 || orient.x > 1 || orient.y < -1 || orient.y > 1 ||
		orient.z < -1 || orient.z > 1)
		scene->mistake = 0;
	return (orient);
}

t_xyzpoint	pars_center(char **line, t_scene *scene)
{
	t_xyzpoint	center;

	if ((!line || !(*line) || (!(ft_isdigit(**line)) && !(**line == '-')))
		&& !(scene->mistake = 0))
		return (init_center());
	center.x = pars_double(0, line);
	if (**line != ',' && !(scene->mistake = 0))
		return (center);
	(*line)++;
	if ((!line || !(*line) || (!(ft_isdigit(**line)) && !(**line == '-')))
		&& !(scene->mistake = 0))
		return (center);
	center.y = pars_double(0, line);
	if (**line != ',' && !(scene->mistake = 0))
		return (center);
	(*line)++;
	if ((!line || !(*line) || (!(ft_isdigit(**line)) && !(**line == '-')))
		&& !(scene->mistake = 0))
		return (center);
	center.z = pars_double(0, line);
	return (center);
}

double		pars_double(double x, char **line)
{
	double	y;
	int		znak;

	y = 1;
	znak = 1;
	if (**line == '-')
	{
		(*line)++;
		znak = -1;
	}
	while (line && *line && **line && ft_isdigit(**line))
	{
		x = x * 10 + **line - '0';
		(*line)++;
	}
	if (**line == '.')
		(*line)++;
	while (line && *line && **line && ft_isdigit(**line))
	{
		x = x + (**line - '0') / (10 * y);
		y++;
		(*line)++;
	}
	return (x * znak);
}

int			pars_line(char *line, t_scene *scene)
{
	if (!line || *line == '#' || *line == '\0')
		return (0);
	while (*line == ' ')
		line++;
	if (*line == 'R')
		return (pars_resol(line, scene));
	else if (*line == 'A')
		return (pars_ambient(line, scene));
	else if (*line == 'l')
		return (pars_light(line, scene));
	else if (*line == 'c' && line[1] == ' ')
		return (pars_camera(line, scene));
	else if (*line == 'c' && line[1] == 'y')
		return (pars_cylin(line, scene));
	else if (*line == 's' && line[1] == 'q')
		return (pars_square(line, scene));
	else if (*line == 's' && line[1] == 'p')
		return (pars_sphere(line, scene));
	else if (*line == 't' && line[1] == 'r')
		return (pars_triangle(line, scene));
	else if (*line == 'p' && line[1] == 'l')
		return (pars_plane(line, scene));
	else
		return (write(2, "wronge scene\n", 13));
}

void		parser(t_scene *scene, int fd)
{
	size_t		i;
	char		*line;

	line = NULL;
	init_scene(scene);
	while ((i = get_next_line(fd, &line)) > 0)
	{
		if (pars_line(line, scene) != 0)
		{
			scene->mistake = 0;
			break ;
		}
		if (line)
			free(line);
		line = NULL;
	}
	if (i == 0)
	{
		if (pars_line(line, scene) != 0)
			scene->mistake = 0;
	}
	if (line)
		free(line);
}
