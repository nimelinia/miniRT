/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_light_resol.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:52:27 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/19 23:09:25 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft/libft.h"
#include "get_next_line.h"
#include "minilibx_mms/mlx.h"

int		pars_light_list(char *line, t_scene *scene)
{
	line++;
	while (line && *line == ' ')
		line++;
	scene->light->center = pars_center(&line, scene);
	while (line && *line == ' ')
		line++;
	if (!line || !(ft_isdigit(*line)))
		return (write(2, "Error\nwrong light\n", 18));
	scene->light->racio = pars_double(0, &line);
	if ((scene->light->racio < 0 || scene->light->racio > 1))
		return (write(2, "Error\nwrong light\n", 18));
	while (line && *line == ' ')
		line++;
	if (!line || !(ft_isdigit(*line)))
		return (write(2, "Error\nwrong light\n", 18));
	scene->light->colour = pars_colour(&line, scene);
	if (!scene->mistake)
		return (write(2, "Error\nwrong light\n", 18));
	return (0);
}

int		pars_light(char *line, t_scene *scene)
{
	static int	count = 0;
	t_light		*new;

	if (count == 0)
	{
		count = 1;
		scene->light->count++;
		return (pars_light_list(line, scene));
	}
	else
	{
		count = 0;
		new = l_init();
		new->next = scene->light;
		scene->light = new;
		return (pars_light(line, scene));
	}
}

int		pars_ambient(char *line, t_scene *scene)
{
	line++;
	while (line && *line == ' ')
		line++;
	if (!line || !(ft_isdigit(*line)))
		return (write(1, "Error\nwrong ambient\n", 20));
	scene->ambi.racio = pars_double(0, &line);
	if ((scene->ambi.racio <= 0 || scene->ambi.racio > 1))
		return (write(2, "Error\nwrong ambient\n", 20));
	while (line && *line == ' ')
		line++;
	if (!line || !(ft_isdigit(*line)))
		return (write(2, "Error\nwrong ambient\n", 20));
	scene->ambi.colour = pars_colour(&line, scene);
	if (!scene->mistake)
		return (write(2, "Error\nwrong ambient\n", 20));
	scene->ambi.count++;
	return (0);
}

int		pars_resol(char *line, t_scene *scene)
{
	line++;
	while (line && *line == ' ')
		line++;
	while (line && ft_isdigit(*line))
	{
		scene->resol.x_size = scene->resol.x_size * 10 + *line - '0';
		line++;
	}
	while (line && *line == ' ')
		line++;
	while (line && ft_isdigit(*line))
	{
		scene->resol.y_size = scene->resol.y_size * 10 + *line - '0';
		line++;
	}
	scene->resol.count++;
	if (scene->resol.x_size <= 0 || scene->resol.y_size <= 0)
	{
		return (write(2, "Error\nwrong resolution\n", 23));
		scene->mistake = 0;
	}
	return (0);
}
