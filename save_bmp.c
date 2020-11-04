/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:52:29 by scopycat          #+#    #+#             */
/*   Updated: 2020/11/03 12:17:44 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"
#include "get_next_line.h"

void	put_image_bmp(t_scene *scene)
{
	char			*name;
	t_file_header	header;
	t_bmp_info		bmpi;

	name = scene->scene_name;
	name[ft_strlen(name) - 2] = '\0';
	name = ft_strjoin_gnl(name, "bmp");
	header.file_size = scene->resol.x_size * scene->resol.y_size * 4 + 54;
	header.signature = 0x4D42;
	header.offset_to_pix = 54;
	header.reserved = 0;
	bmpi.headersize = 40;
	bmpi.plane = 1;
	bmpi.weight = scene->resol.x_size;
	bmpi.hight = scene->resol.y_size;
	bmpi.bpp = g_mlx.bpp;
	bmpi.compress = 0;
	bmpi.imagesize = scene->resol.x_size * scene->resol.y_size * 4;
	bmpi.bpmx = 0;
	bmpi.bpmy = 0;
	bmpi.colour = 0;
	bmpi.colout_imp = 0;
	fill_bmp(bmpi, header, name, scene);
}

void	fill_bmp(t_bmp_info bmpi, t_file_header header, char *name, \
		t_scene *scene)
{
	int	fd;
	int i;

	i = 0;
	fd = open(name, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	i = write(fd, &header.signature, 2);
	i += write(fd, &header.file_size, 4);
	i += write(fd, &header.reserved, 4);
	i += write(fd, &header.offset_to_pix, 4);
	i += write(fd, &bmpi.headersize, 4);
	i += write(fd, &bmpi.weight, 4);
	i += write(fd, &bmpi.hight, 4);
	i += write(fd, &bmpi.plane, 2);
	i += write(fd, &bmpi.bpp, 2);
	i += write(fd, &bmpi.compress, 4);
	i += write(fd, &bmpi.imagesize, 4);
	i += write(fd, &bmpi.bpmx, 4);
	i += write(fd, &bmpi.bpmy, 4);
	i += write(fd, &bmpi.colour, 4);
	i += write(fd, &bmpi.colout_imp, 4);
	if ((i != 54) || fill_pixels(fd, scene->resol.x_size, scene->resol.y_size)\
		!= (bmpi.imagesize - 1))
		exit(1);
	close(fd);
	exit(0);
}

int		fill_pixels(int fd, int x, int y)
{
	int				i;
	unsigned char	*pic;

	pic = (unsigned char*)g_mlx.addr;
	i = 0;
	while (y-- >= 0)
		i += write(fd, &pic[g_mlx.length * y], x * 4);
	return (i);
}
