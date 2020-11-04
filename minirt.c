/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 19:20:04 by scopycat          #+#    #+#             */
/*   Updated: 2020/11/03 12:18:48 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "get_next_line.h"
#include "minilibx_mms/mlx.h"

static void	check_scene(t_scene *scene)
{
	if (scene->camera->count < 1 || scene->ambi.count != 1 ||
		scene->resol.count != 1)
	{
		scene->mistake = 0;
		write(2, "Error\nwrong scene\n", 18);
		exit(free_struct(scene));
	}
}

static void	check_extent(char *line)
{
	if (ft_strncmp(&(line[ft_strlen(line) - 3]), ".rt", 4))
	{
		write(2, "Error\nInvalid file extension\n", 29);
		exit(1);
	}
}

double		check_save(char *frase)
{
	char	*save;

	save = "--save";
	return (ft_strncmp(frase, save, 7));
}

int			minirt(int argc, char **argv)
{
	char	*line;
	int		fd;
	t_scene	scene;

	if (argc != 2 && !(argc == 3 && !check_save(argv[2])))
		return (write(2, "Error\nerror of quantity of arguments\n", 37));
	line = argv[1];
	check_extent(line);
	if ((fd = open(line, O_RDONLY)) < 0)
		exit(write(2, "Error\ncheck the file\n", 21));
	parser(&scene, fd);
	close(fd);
	t_init_points(&scene);
	check_scene(&scene);
	if (argc == 3 && !check_save(argv[2]))
	{
		scene.save = 1;
		scene.scene_name = ft_strdup(argv[1]);
	}
	else
		scene.save = 0;
	if (scene.mistake)
		start_work(&scene);
	return (0);
}

int			main(int argc, char **argv)
{
	minirt(argc, argv);
	return (0);
}
