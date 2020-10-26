/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_mlx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 21:14:12 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/26 20:59:46 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft/libft.h"
#include "get_next_line.h"
#include "minilibx_mms/mlx.h"
#include <stdio.h>

void	start_work(t_scene *scene)
{
	// t_mlx	mlx;
	// void	*mlx_ptr;
	// void	*win_ptr;
	// void	*image;
	// int		x = 0;
	// int		y = 0;

	g_mlx = init_mlx();
	g_mlx.m_ptr = mlx_init();
	// mlx->w_ptr = NULL;
	if (scene->save == 0)
		g_mlx.w_ptr = mlx_new_window(g_mlx.m_ptr, scene->resol.x_size, scene->resol.y_size, "miniRT");
	// while(x <= scene->resol.x_size)
	// {
	// 	while (y<= scene->resol.y_size)
	// 	{
	// 		mlx_pixel_put(mlx_ptr, win_ptr, x, y, convert_colour(scene->ambi.colour, scene->ambi.racio));
	// 		y++;
	// 	}
	// 	x++;
	// 	y = 0;
	// }
	g_mlx.img = mlx_new_image(g_mlx.m_ptr, scene->resol.x_size, scene->resol.y_size);
	g_mlx.addr = mlx_get_data_addr(g_mlx.img, &g_mlx.bpp, &g_mlx.length, &g_mlx.end);
	g_scene = scene;
	g_camera = scene->camera;
	copy_struct(g_scene);
	check_cam(g_scene_copy);
	prerender(g_scene_copy, &g_mlx);
	// очистка g_scene_copy
	// g_mlx = mlx;
	
	// g_scene = scene;
	// render(scene, mlx);
	// render(scene, mlx_ptr, win_ptr);
	if (g_mlx.w_ptr)
	{
		mlx_put_image_to_window(g_mlx.m_ptr, g_mlx.w_ptr, g_mlx.img, 0, 0);
		mlx_hook(g_mlx.w_ptr, 17, 1L << 17, free_struct, scene);
		mlx_hook(g_mlx.w_ptr, 2, 1L << 0, key_pressed, scene);
	}
	
	// else
		// сохранение в bmp	и очистка
	mlx_loop(g_mlx.m_ptr);
	
}

int		key_pressed(int	keycode, t_scene *scene)
{
	if (keycode == 53)
		return(free_struct(scene));
	if (keycode == 8)
	{
		if (g_scene->camera->next)
			g_scene->camera = g_scene->camera->next;
		else if (g_scene->camera == g_camera)
			return (0);
		else
			g_scene->camera = g_camera;
		free_points(g_scene); // возможно не понадобится
		mlx_destroy_image(g_mlx.m_ptr, g_mlx.img);
		// mlx_clear_window(g_mlx.m_ptr, g_mlx.w_ptr);
		g_mlx.img = mlx_new_image(g_mlx.m_ptr, scene->resol.x_size, scene->resol.y_size);
		g_mlx.addr = mlx_get_data_addr(g_mlx.img, &g_mlx.bpp, &g_mlx.length, &g_mlx.end);
		copy_struct(g_scene);
		check_cam(g_scene_copy);
		prerender(g_scene_copy, &g_mlx);
		//очистить g_scene_copy
		mlx_put_image_to_window(g_mlx.m_ptr, g_mlx.w_ptr, g_mlx.img, 0, 0);
	}
	return (0);
}

void		free_points(t_scene *scene)
{
	int		x;
	int		y;

	x = scene->resol.x_size;
	y = scene->resol.y_size;
	while (x >= 0)
	{
		while (y >= 0)
		{
			scene->points[x][y] = MAXFLOAT;
			y--;
		}
		y = scene->resol.y_size;
		x--;
	}
}

void	check_cam(t_scene *scene)
{
	scene->camera->orient = normalize_vector(scene->camera->orient);
	if (scene->camera->center.x != 0 || scene->camera->center.y != 0 || 
		scene->camera->center.z != 0 || scene->camera->orient.x != 0 || 
		scene->camera->orient.y != 0 || scene->camera->orient.z != 1)
		change_coordinates_all(scene, rotate_matrix(scene));
}

void	change_coordinates_all(t_scene *scene, t_matrix matrix)
{
	change_light_coor(scene, matrix);
	change_sphere_coor(scene, matrix);
	change_plane_coor(scene, matrix);
	change_triangle_coor(scene, matrix);
	change_square_coor(scene, matrix);
	change_cylin_coor(scene, matrix);
}

void	change_light_coor(t_scene *scene, t_matrix matrix)
{
	t_light	*tmp_l;

	tmp_l = scene->light;
	while(scene->light)
	{
		scene->light->center = mult_point_matrix(scene->light->center, matrix);
		scene->light = scene->light->next;
	}
	scene->light = tmp_l;
}

void	change_sphere_coor(t_scene *scene, t_matrix matrix)
{
	t_sphere	*tmp_sp;

	tmp_sp = scene->sphere;
	while(scene->sphere)
	{
		scene->sphere->center = mult_point_matrix(scene->sphere->center, matrix);
		scene->sphere = scene->sphere->next;
	}
	scene->sphere = tmp_sp;
}

void	change_plane_coor(t_scene *scene, t_matrix matrix)
{
	t_plane	*tmp_pl;

	tmp_pl = scene->plane;
	while(scene->plane)
	{
		scene->plane->center = mult_point_matrix(scene->plane->center, matrix);
		scene->plane->orient = mult_point_matrix(scene->plane->orient, matrix);
		scene->plane = scene->plane->next;
	}
	scene->plane = tmp_pl;
}

void	change_triangle_coor(t_scene *scene, t_matrix matrix)
{
	t_triangle	*tmp_tr;

	tmp_tr = scene->triangle;
	while(scene->triangle)
	{
		scene->triangle->angle_one = mult_point_matrix(scene->triangle->angle_one, matrix);
		scene->triangle->angle_two = mult_point_matrix(scene->triangle->angle_two, matrix);
		scene->triangle->angle_three = mult_point_matrix(scene->triangle->angle_three, matrix);
		scene->triangle = scene->triangle->next;
	}	
	scene->triangle = tmp_tr;
}

void change_square_coor(t_scene *scene, t_matrix matrix)
{
	t_square	*tmp_sq;

	tmp_sq = scene->square;
	while(scene->square)
	{
		scene->square->center = mult_point_matrix(scene->square->center, matrix);
		scene->square->orient = mult_point_matrix(scene->square->orient, matrix);
		scene->square = scene->square->next;
	}
	scene->square = tmp_sq;
}

void	change_cylin_coor(t_scene *scene, t_matrix matrix)
{
	t_cylin	*tmp_cy;

	tmp_cy = scene->cylin;
	while(scene->cylin)
	{
		scene->cylin->center = mult_point_matrix(scene->cylin->center, matrix);
		scene->cylin->orient = mult_point_matrix(scene->cylin->orient, matrix);
		scene->cylin = scene->cylin->next;
	}
	scene->cylin = tmp_cy;
}

t_xyzpoint	mult_point_matrix(t_xyzpoint point, t_matrix matrix)
{
	t_xyzpoint	result;

	result.x = matrix.str_1.x * point.x + matrix.str_1.y * point.y + matrix.str_1.z * point.z;
	result.y = matrix.str_2.x * point.x + matrix.str_2.y * point.y + matrix.str_2.z * point.z;
	result.z = matrix.str_3.x * point.x + matrix.str_3.y * point.y + matrix.str_3.z * point.z;
	return (result);
}

void		copy_struct(t_scene *orig_scene)
{
	t_scene		scene_cp;

	init_scene(&scene_cp);
	scene_cp.ambi = orig_scene->ambi;
	scene_cp.resol = orig_scene->resol;
	copy_camera(orig_scene, &scene_cp);
	copy_light(orig_scene, &scene_cp);
	copy_sphere(orig_scene, &scene_cp);
	copy_plane(orig_scene, &scene_cp);
	copy_triangle(orig_scene, &scene_cp);
	copy_square(orig_scene, &scene_cp);
	copy_cylin(orig_scene, &scene_cp);
	t_init_points(&scene_cp);
	g_scene_copy = &scene_cp;
}

void	copy_camera(t_scene *orig_scene, t_scene *scene_cp) // тут спецом копируется только одна камера
{	
	scene_cp->camera->center = orig_scene->camera->center;
	scene_cp->camera->fov = orig_scene->camera->fov;
	scene_cp->camera->orient = orig_scene->camera->orient;
}

void	copy_light(t_scene *orig_scene, t_scene *scene_cp)
{
	t_light *tmp_l;
	t_light	*new;
	int		i;

	i = 1;
	tmp_l = orig_scene->light;
	while (orig_scene->light)
	{
		scene_cp->light->racio = orig_scene->light->racio;
		scene_cp->light->center = orig_scene->light->center;
		scene_cp->light->colour = orig_scene->light->colour;
		scene_cp->light->count = i++;
		orig_scene->light = orig_scene->light->next;
		if (orig_scene->light)
		{
			new = l_init();
			new->next = scene_cp->light;
			scene_cp->light = new;
		}
	}
	orig_scene->light = tmp_l;
}

void	copy_sphere(t_scene *orig_scene, t_scene *scene_cp)
{
	t_sphere	*tmp_sp;
	t_sphere	*new;
	int			i;

	i = 1;
	tmp_sp = orig_scene->sphere;
	while (orig_scene->sphere)
	{
		scene_cp->sphere->center = orig_scene->sphere->center;
		scene_cp->sphere->colour = orig_scene->sphere->colour;
		scene_cp->sphere->diametr = orig_scene->sphere->diametr;
		scene_cp->sphere->count = i++;
		orig_scene->sphere = orig_scene->sphere->next;
		if (orig_scene->sphere)
		{
			new = sp_init();
			new->next = scene_cp->sphere;
			scene_cp->sphere = new;
		}
	}
	orig_scene->sphere = tmp_sp;
}

void	copy_plane(t_scene *orig_scene, t_scene *scene_cp)
{
	t_plane		*tmp_pl;
	t_plane		*new;
	int			i;

	tmp_pl = orig_scene->plane;
	i = 1;
	while (orig_scene->plane)
	{
		scene_cp->plane->center = orig_scene->plane->center;
		scene_cp->plane->colour = orig_scene->plane->colour;
		scene_cp->plane->orient = orig_scene->plane->orient;
		scene_cp->plane->count = i++;
		orig_scene->plane = orig_scene->plane->next;
		if (orig_scene->plane)
		{
			new = p_init();
			new->next = scene_cp->plane;
			scene_cp->plane = new;
		}
	}
	orig_scene->plane = tmp_pl;
}

void	copy_triangle(t_scene *orig_scene, t_scene *scene_cp)
{
	t_triangle	*tmp_tr;
	t_triangle	*new;
	int			i;

	i = 1;
	tmp_tr = orig_scene->triangle;
	while (orig_scene->triangle)
	{
		scene_cp->triangle->angle_one = orig_scene->triangle->angle_one;
		scene_cp->triangle->angle_two = orig_scene->triangle->angle_two;
		scene_cp->triangle->angle_three = orig_scene->triangle->angle_three;
		scene_cp->triangle->colour = orig_scene->triangle->colour;
		scene_cp->triangle->count = i++;
		orig_scene->triangle = orig_scene->triangle->next;
		if (orig_scene->triangle)
		{
			new = t_init();
			new->next = scene_cp->triangle;
			scene_cp->triangle = new;
		}
	}
	orig_scene->triangle = tmp_tr;
}

void	copy_square(t_scene *orig_scene, t_scene *scene_cp)
{
	t_square	*tmp_sq;
	t_square	*new;
	int			i;

	i = 1;
	tmp_sq = orig_scene->square;
	while (orig_scene->square)
	{
		scene_cp->square->center = orig_scene->square->center;
		scene_cp->square->colour = orig_scene->square->colour;
		scene_cp->square->lenght = orig_scene->square->lenght;
		scene_cp->square->orient = orig_scene->square->orient;
		scene_cp->square->count = i++;
		orig_scene->square = orig_scene->square->next;
		if (orig_scene->square)
		{
			new = sq_init();
			new->next = scene_cp->square;
			scene_cp->square = new;
		}
	}
	orig_scene->square = tmp_sq;
}

void	copy_cylin(t_scene *orig_scene, t_scene *scene_cp)
{
	t_cylin		*tmp_cy;
	t_cylin		*new;
	int			i;

	i = 1;
	tmp_cy = orig_scene->cylin;
	while (orig_scene->cylin)
	{
		scene_cp->cylin->center = orig_scene->cylin->center;
		scene_cp->cylin->colour = orig_scene->cylin->colour;
		scene_cp->cylin->diametr = orig_scene->cylin->diametr;
		scene_cp->cylin->lenght = orig_scene->cylin->lenght;
		scene_cp->cylin->orient = orig_scene->cylin->orient;
		scene_cp->cylin->count = i++;
		orig_scene->cylin = orig_scene->cylin->next;
		if (orig_scene->cylin)
		{
			new = cy_init();
			new->next = scene_cp->cylin;
			scene_cp->cylin = new;
		}
	}
	orig_scene->cylin = tmp_cy;
}

void		my_mlx_pixel_put(t_mlx *mlx, int x, int y, int colour)
{
	int		offset;

	offset = (y * mlx->length + x * (mlx->bpp / 8));
	*(unsigned int*)(mlx->addr + offset) = colour;
}

t_xyzpoint	find_point_coordinates(t_xyzpoint cntr, t_xyzpoint orient, double s)
{
	t_xyzpoint	result;

	result.x = cntr.x + orient.x * s;
	result.y = cntr.y + orient.y * s;
	result.z = cntr.z + orient.z * s;
	return (result);
}

double		length_to_pl_point(t_xyzpoint start, t_xyzpoint normal, t_xyzpoint pl_point, t_xyzpoint vect)
{
	double	d;
	double	lenght;
	
	d = -scalar(pl_point, normal);
	lenght = -(d + scalar(normal, start)) / scalar(normal, vect);
	return (lenght);
}


t_xyzpoint		mult_num_vect(t_xyzpoint vector, double num)
{
	t_xyzpoint	result;

	result.x = vector.x * num;
	result.y = vector.y * num;
	result.z = vector.z * num;
	return (result);
}



t_xyzpoint	find_center_canvas(t_scene *scene, int x, int y)
{
	t_xyzpoint	fin_coord;
	double		weight;
	double		hight;
	// t_xyzpoint	new_camera;

	// new_camera = rotate_matrix(scene);
	weight = find_weight_screen(scene);
	hight = weight * scene->resol.y_size / scene->resol.x_size;
	fin_coord.x = (scene->camera->center.x + scene->camera->orient.x + x - scene->resol.x_size / 2) * weight / scene->resol.x_size;
	fin_coord.y = (scene->camera->center.y + scene->camera->orient.y + y - scene->resol.y_size / 2) * hight / scene->resol.y_size;
	fin_coord.z = scene->camera->center.z + scene->camera->orient.z;
	return (fin_coord);
}

t_matrix	rotate_matrix(t_scene *scene)
{
	double		angle_one;
	double		angle_sec;
	t_matrix	rot_matr;

	angle_one = acos(scene->camera->orient.z);
	angle_sec = asin(scene->camera->orient.y);
	rot_matr.str_1.x = cos(angle_one);
	rot_matr.str_1.y = sin(angle_one) * sin(angle_sec);
	rot_matr.str_1.z = sin(angle_one) * cos(angle_sec);
	rot_matr.str_2.x = 0;
	rot_matr.str_2.y = cos(angle_sec);
	rot_matr.str_2.z = - sin(angle_sec);
	rot_matr.str_3.x = - sin(angle_one);
	rot_matr.str_3.y = cos(angle_one) * sin(angle_sec);
	rot_matr.str_3.z = cos(angle_one) * cos(angle_sec);
	return (rot_matr);
}

double	find_weight_screen(t_scene *scene)
{
	double	a;
	double	b;
	
	a = length_vector(scene->camera->orient);
	b = a * tan(scene->camera->fov * M_PI/ 360);
	return (b * 2);
}

int		free_struct(t_scene *scene) // дописать очистку
{
	if (scene->camera)
		free(scene->camera);
	exit (0);
}



// double	check_light_2(t_scene *scene, int x, int y, t_index fig)
// {
// 	t_xyzpoint	point;
// 	t_xyzpoint	figure_normal;
// 	t_xyzpoint	light;
// 	double		res;
// 	int			i;
// 	t_light		*tmp_l;

// 	tmp_l = scene->light;
// 	i = fig.ind_l_n;
// 	while (i--)
// 		tmp_l = tmp_l->next;
// 	res = 0.0;
// 	figure_normal = find_figure_center(scene, fig, find_center_canvas(scene, x, y));
// 	// canvas = normalize_vector(canvas);
// 	point = find_point_coordinates(scene->camera->center, find_center_canvas(scene, x, y), fig.t); //точка на плоскости
// 	light = substruct_vector(tmp_l->center, point);
// 	light = normalize_vector(light);
// 	// if (scalar(figure_normal, light) < 0) //если косинус меньше 0, то значит угол тупой
// 	// 	res = -(scene->light->racio * scalar(figure_normal, light));
// 	if (scalar(figure_normal, light) > 0) //вектор нормали смотрит в сторону камеры, если вектор из точки
// 		res = (tmp_l->racio * scalar(figure_normal, light)); // в источник света смотрит туда же, то она этим светом освещена
// 	// if (check_shadows_2(substruct_vector(scene->light->center, point), scene))
// 	// if (check_shadows_all(substruct_vector(point, scene->light->center), scene, t))
// 	if (check_shadows_all(substruct_vector(tmp_l->center, point), scene, fig))
// 		res = 0.0;
// 	return (res);
// }

// double			check_shadows_sphere(t_sphere *current_sp, t_xyzpoint light, t_scene *scene, t_index fig)
// {
// 	double		length;
// 	double		length_cur;
// 	t_light		*tmp_l;
// 	int			i;
	
// 	i = fig.ind_l_n;
// 	tmp_l = scene->light;
// 	while (i--)
// 		tmp_l = tmp_l->next;
// 	while (current_sp)
// 	{
// 		if (fig.ind_fig != 1 || (fig.count - fig.ind_fig_n) != current_sp->count) // current_sp != scene->sphere) // тут нужно проверить, что это не эта сфера (сравнить с count)
// 		{
// 			length = length_vector(vector_mult(light, substruct_vector(tmp_l->center, current_sp->center))) / length_vector(light);
// 			length_cur = sqrt(pow(length_vector(substruct_vector(tmp_l->center, current_sp->center)), 2) - pow(length, 2));
// 			if (length <= (current_sp->diametr / 2) && length_vector(light) > length_cur &&
// 			scalar(light, substruct_vector(tmp_l->center, current_sp->center)) > 0)
// 				return (1);
// 		}
// 		current_sp = current_sp->next;
// 	}
// 	return (0);
// }

// double			check_shadows_plane(t_plane *current_pl, t_xyzpoint light, t_scene *scene, t_index fig) // функция кривая, надо переписывать. хз как
// {
// 	double		d; // перпендикуляр из света к плоскости
// 	double		length;
// 	t_light		*tmp_l;
// 	int			i;
	
// 	i = fig.ind_l_n;
// 	tmp_l = scene->light;
// 	while (i--)
// 		tmp_l = tmp_l->next;
// 	// double		length_cur;

// 	// light = mult_num_vect(light, -1);
// 	while (current_pl)
// 	{
// 		if (fig.ind_fig != 2 || (fig.count - fig.ind_fig_n) != current_pl->count) // current_pl != scene->plane)
// 		{	
// 			current_pl->orient = normalize_orient(current_pl->center, current_pl->orient, g_scene->camera->center);
// 			d = -scalar(current_pl->center, current_pl->orient);
// 			length = -(d + scalar(current_pl->orient, tmp_l->center)) / \
// 			scalar(current_pl->orient, mult_num_vect(light, -1));
// 			if (length_vector(light) > length && scalar(normalize_vector(light), current_pl->orient) < 0 && length > 0)
// 			// if (length_vector(light) > length && scalar(normalize_vector(light), normalize_vector(current_pl->orient)) < 0)
// 				return (1);
// 			// d = -scalar(current_pl->center, current_pl->orient); // тут должен быть минус
// 			// d = -(scalar(current_pl->orient, scene->light->center) + d) / length_vector(current_pl->orient);
// 			// length = length_vector(vector_mult(mult_num_vect(normalize_vector(current_pl->orient), d), light)) / length_vector(light);
// 			// length_cur = d / sin(acos(length / d));
// 			// if (length_vector(light) > length_cur && scalar(normalize_vector(light), current_pl->orient) < 0 && length_cur > 0) // тут должно быть меньше 0
// 			// 	return (1);
// 		}
// 		current_pl = current_pl->next;
// 	}
// 	return (0);
// }


// double			check_shadows_triangle(t_triangle *current_tr, t_xyzpoint light, t_scene *scene, t_index fig) // функция кривая, надо переписывать. хз как
// {
// 	// double		d; // перпендикуляр из света к плоскости
// 	double		length;
// 	t_xyzpoint	antilight;
// 	t_light		*tmp_l;
// 	int			i;
	
// 	i = fig.ind_l_n;
// 	tmp_l = scene->light;
// 	while (i--)
// 		tmp_l = tmp_l->next;
// 	antilight = normalize_vector(mult_num_vect(light, -1));
// 	while (current_tr)
// 	{
// 		if (fig.ind_fig != 3 || (fig.count - fig.ind_fig_n) != current_tr->count)// current_tr != scene->triangle)
// 		{
// 			current_tr->normal = vector_mult(substruct_vector(current_tr->angle_two, \
// 				current_tr->angle_one), substruct_vector(current_tr->angle_three, current_tr->angle_one));
// 			current_tr->normal = normalize_orient(current_tr->angle_one, current_tr->normal, g_scene->camera->center);
// 			length = length_to_pl_point(tmp_l->center, current_tr->normal, current_tr->angle_one, antilight);
			
// 			// d = -scalar(current_tr->angle_one, current_tr->normal);
// 			// length = -(d + scalar(current_tr->normal, tmp_l->center)) / \
// 			// scalar(current_tr->normal, antilight);
// 			if (check_inside_triangle(tmp_l->center, current_tr, antilight, length) && 
// 				// (scalar(normalize_vector(light), current_tr->normal) != 0 || length > 0) && length < length_vector(light)) // здесь свет - это из точки на свет
// 				length > 0 && length < length_vector(light))
// 				 //scalar(normalize_vector(light), current_tr->normal) < 0
// 				return (1);

// 			// current_tr->normal = vector_mult(substruct_vector(current_tr->angle_two, \
// 			// 	current_tr->angle_one), substruct_vector(current_tr->angle_three, current_tr->angle_one));
// 			// current_tr->normal = normalize_orient(current_tr->angle_one, current_tr->normal, scene->camera->center);
// 			// length = (scalar(current_tr->angle_two, current_tr->normal) - scalar(current_tr->normal, \
// 			// 	scene->light->center)) / scalar(current_tr->normal, antilight);
// 			// if (check_inside_triangle(scene->light->center, current_tr, antilight, length) && 
// 			// 	scalar(normalize_vector(light), current_tr->normal) != 0 && length > 0 && length < length_vector(light)) // здесь свет - это из точки на свет
// 			// 	return (1);
// 		}
// 		current_tr = current_tr->next;
// 	}
// 	return (0);
// }

// double			check_shadows_square(t_square *current_sq, t_xyzpoint light, t_scene *scene, t_index fig) // функция кривая, надо переписывать. хз как
// {
// 	// double		d; // перпендикуляр из света к плоскости
// 	double		length;
// 	t_xyzpoint	antilight;
// 	t_light		*tmp_l;
// 	int			i;
	
// 	i = fig.ind_l_n;
// 	tmp_l = scene->light;
// 	while (i--)
// 		tmp_l = tmp_l->next;
// 	antilight = normalize_vector(mult_num_vect(light, -1));
// 	while (current_sq)
// 	{
// 		if (fig.ind_fig != 4 || (fig.count - fig.ind_fig_n) != current_sq->count)//current_sq != scene->square)
// 		{	
// 			// current_sq->orient = normalize_orient(current_sq->center, current_sq->orient, scene->camera->center);
// 			// // current_sq->orient = mult_num_vect(current_sq->orient, -1);
// 			// // d = -scalar(current_sq->center, current_sq->orient);
// 			// // length = -(d + scalar(current_sq->orient, scene->light->center) / \
// 			       // // scalar(current_sq->orient, antilight));
// 			// length = (scalar(current_sq->center, current_sq->orient) - \
// 			// 	scalar(current_sq->orient,  scene->camera->center)) / \
// 			// 	scalar(current_sq->orient, antilight);
// 			// if (check_inside_square(scene->light->center, current_sq, antilight, length) && 
// 			// 	scalar(normalize_vector(light), current_sq->orient) != 0 && length > 0 && length < length_vector(light))//mult_num_vect(current_sq->orient, -1)) > 0) // здесь свет - это из точки на свет
// 			// 	return (1);
			
// 			// current_sq->orient = normalize_orient(current_sq->center, current_sq->orient, g_scene->camera->center);
// 			length = length_to_pl_point(tmp_l->center, current_sq->orient, current_sq->center, antilight);
// 			// d = -scalar(current_sq->center, current_sq->orient);
// 			// length = fabs((d + scalar(current_sq->orient, tmp_l->center)) / \
// 			// scalar(current_sq->orient, normalize_vector(light)));
// 			// length = -(scalar(current_sq->center, current_sq->orient) - \
// 			// 	scalar(current_sq->orient, g_scene->camera->center)) / \
// 			// 	scalar(current_sq->orient, normalize_vector(light));
// 			// double tech = length_vector(light);
// 			// (void)tech;
// 			if (check_inside_square(tmp_l->center, current_sq, normalize_vector(light), length) && 
// 				length > 0 && length < length_vector(light))
// 				// (scalar(light, current_sq->orient) > 0 && length > 0) && length < length_vector(light))//mult_num_vect(current_sq->orient, -1)) > 0) // здесь свет - это из точки на свет
// 				return (1);
// 		}
// 		current_sq = current_sq->next;
// 	}
// 	return (0);
// }

// double			check_shadows_cylin(t_cylin *current_cy, t_xyzpoint light, t_scene *scene, t_index fig) // функция кривая, надо переписывать. хз как
// {
// 	// t_cylin		*temp;
// 	// t_xyzpoint	canvas;
// 	// t_xyzpoint	temp_2;
// 	t_light		*tmp_l;
// 	int			i;
// 	double		length;
	
// 	i = fig.ind_l_n;
// 	tmp_l = scene->light;
// 	while (i--)
// 		tmp_l = tmp_l->next;
// 	light = mult_num_vect(light, -1);
// 	// canvas = find_point_coordinates(scene->light->center, normalize_vector(light), -0.1);
// 	while (current_cy)
// 	{
// 		if (fig.ind_fig != 5 || (fig.count - fig.ind_fig_n) != current_cy->count) //current_cy != scene->cylin)
// 		{
// 			// temp = scene->cylin;
// 			// temp_2 = scene->camera->center;
// 			// scene->camera->center = scene->light->center;
// 			// scene->cylin = current_cy;
// 			length = check_cylin_wall(current_cy, normalize_vector(light), MAXFLOAT, tmp_l->center);
// 			if (length < length_vector(light) && length)
// 				return (1);
// 			// if (check_cylin_wall(current_cy, normalize_vector(light), MAXFLOAT, tmp_l->center) < length_vector(light) &&
// 			// check_cylin_wall(scene, normalize_vector(light), MAXFLOAT, canvas))
// 			// 	return (1);
// 			// 	{
// 			// 		scene->cylin = temp;
// 			// 		scene->camera->center = temp_2;
// 			// 		return (1);
// 			// 	}
// 			// scene->cylin = temp;
// 			// scene->camera->center = temp_2;
// 			// length = length_vector(vector_mult(light, substruct_vector(scene->light->center, current_cy->center))) / length_vector(light);
// 			// if (length == 0)
// 			// 	return (1);
// 			// length_cur = sqrt(pow(length_vector(substruct_vector(scene->light->center, current_cy->center)), 2) - pow(length, 2));
// 			// if (check_length_cylin(scene, current_cy, length, light) && length_vector(light) > length_cur &&
// 			// scalar(light, substruct_vector(scene->light->center, current_cy->center)) != -1)
// 			// 	return (1);
// 		}
// 		current_cy = current_cy->next;
// 	}
// 	return (0);
// }

// double			check_shadows_cylin(t_cylin *current_cy, t_xyzpoint light, t_scene *scene, double *t) // функция кривая, надо переписывать. хз как
// {
// 	double	length;
// 	double	length_cur;

// 	while (current_cy)
// 	{
// 		if (t[1] != 5 || current_cy != scene->cylin)
// 		{
// 			current_cy->normal = find_cylin_normal_2(current_cy, scene);
// 			length = length_vector(vector_mult(light, substruct_vector(scene->light->center, current_cy->center))) / length_vector(light);
// 			if (length == 0)
// 				return (1);
// 			length_cur = sqrt(pow(length_vector(substruct_vector(scene->light->center, current_cy->center)), 2) - pow(length, 2));
// 			if (check_length_cylin(scene, current_cy, length, light) && length_vector(light) > length_cur &&
// 			scalar(light, substruct_vector(scene->light->center, current_cy->center)) != -1)
// 				return (1);
// 		}
// 		current_cy = current_cy->next;
// 	}
// 	return (0);
// }

// t_xyzpoint	find_cylin_normal_2(t_cylin *cylin, t_scene *scene)
// {
// 	double		hight;
// 	t_xyzpoint	gipot;
// 	t_xyzpoint	normal;
// 	t_xyzpoint	point;
// 	double		lenght;

// 	cylin->orient = normalize_orient(cylin->center, cylin->orient, scene->camera->center); // тут мы нормализуем вектор направления оси цилиндра
// 	gipot = substruct_vector(scene->light->center, cylin->center);
// 	hight = length_vector(vector_mult(cylin->orient, gipot)) / length_vector(cylin->orient);
// 	lenght = sqrt(pow(length_vector(gipot), 2) - pow(hight,2));
// 	point = find_point_coordinates(cylin->center, cylin->orient, lenght);
// 	normal = normalize_vector(substruct_vector(scene->light->center, point));
// 	return (normal);
// }

// double		check_length_cylin(t_scene *scene, t_cylin *cylin, double length, t_xyzpoint light)
// {
// 	t_xyzpoint	point; // центр основания цилиндра
// 	t_xyzpoint	point_2; // край основания цилиндра

// 	point = find_point_coordinates(cylin->center, cylin->orient, cylin->lenght / 2);
// 	point_2 = find_point_coordinates(cylin->center, cylin->orient, - cylin->lenght / 2);
// 	if (length_vector(substruct_vector(scene->light->center, point)) > length_vector(substruct_vector(scene->light->center, point_2)))
// 		point = point_2;
// 	point_2 = find_point_coordinates(point, cylin->normal, - cylin->diametr / 2);
// 	if (length_vector(substruct_vector(scene->light->center, point_2)) > length_vector(substruct_vector(scene->light->center, find_point_coordinates(point, cylin->normal, cylin->diametr / 2))))
// 		point_2 = find_point_coordinates(point, cylin->normal, cylin->diametr / 2);
	
	
// 	// double		angle;
// 	// t_xyzpoint	hight;
// 	// double		l_temp;

// 	// hight = find_point_coordinates(scene->light->center, normalize_vector(light), -length_vector(light));
// 	// hight = substruct_vector(hight, current_cy->center);
// 	// if (scalar(normalize_vector(hight), normalize_vector(current_cy->orient)) < 0)
// 	// 	current_cy->orient = mult_num_vect(current_cy->orient, -1);
// 	// angle = acos(scalar(normalize_vector(hight), normalize_vector(current_cy->orient)));
// 	// if (atan(current_cy->diametr/current_cy->lenght) > angle)
// 	// 	l_temp = (current_cy->lenght / 2) / cos(angle);
// 	// else
// 	// 	l_temp = (current_cy->diametr / 2) / cos(M_PI/4 - angle);
// 	// if (length > l_temp)
// 	// 	return (0);
// 	// else
// 	// 	return (1);
// }


// double			check_shadows(t_xyzpoint light, t_scene *scene)
// {
// 	t_sphere	*current_sp;
// 	double		shadow;
// 	double		length;
// 	double		length_cur;

// 	shadow = 0;
// 	current_sp = g_sphere;
// 	while (current_sp)
// 	{
// 		if (current_sp != scene->sphere)
// 		{
// 			length = length_vector(vector_mult(substruct_vector(scene->light->center, current_sp->center), light)) / length_vector(light);
// 			length_cur = sqrt(pow(length_vector(substruct_vector(scene->light->center, current_sp->center)), 2) - pow(length, 2));
// 			if (length <= (current_sp->diametr / 2) && length_vector(light) > length_cur &&
// 			scalar(light, substruct_vector(scene->light->center, current_sp->center)) > 0)
// 				shadow = 1;
// 		}
// 		current_sp = current_sp->next;
// 	}
// 	return (shadow);
// }


// double			check_shadows_2(t_xyzpoint light, t_scene *scene)
// {
// 	t_sphere	*current_sp;
// 	double		shadow;
// 	double		length;
// 	double		length_cur;

// 	shadow = 0;
// 	current_sp = g_sphere;
// 	while (current_sp)
// 	{
// 		length = length_vector(vector_mult(substruct_vector(scene->light->center, current_sp->center), light)) / length_vector(light);
// 		length_cur = sqrt(pow(length_vector(substruct_vector(scene->light->center, current_sp->center)), 2) - pow(length, 2));
// 		if (length <= (current_sp->diametr / 2) && length_vector(light) > length_cur &&
// 		scalar(light, substruct_vector(scene->light->center, current_sp->center)) > 0)
// 			shadow = 1;
// 		current_sp = current_sp->next;
// 	}
// 	return (shadow);
// }



// double		check_shadows(t_xyzpoint light, t_scene *scene, t_xyzpoint point) // от 0,00001 до 1
// {
// 	double		t1;
// 	double		t2;
// 	double 		close_t;
// 	t_xyzpoint	ray;
// 	t_sphere	*close_sp;

// 	close_t = length_vector(light); // вместо O point, вместо D - ligth
// 	close_sp = scene->sphere;
// 	while (close_sp)
// 	{
// 		ray = substruct_vector(point, close_sp->center);
// 		t1 = find_shadow_t1(light, ray, *close_sp);
// 		t2 = find_shadow_t2(light, ray, *close_sp);
// 		if (t1 >= 0.001 && t1 < close_t)
// 		{
// 			close_t = t1;
// 		}
// 		if (t2 >= 0.001 && t2 < close_t)
// 		{
// 			close_t = t2;
// 		}
// 		close_sp = close_sp->next;
// 		point = find_point(scene, close_sp)
// 	}
// 	if (close_t == length_vector(light))
// 		return (0);
// 	else
// 		return (close_t);
// }

// t_xyzpoint	find_point(t_scene *scene, t_sphere *close_sp)
// {
// 	double			t;
// 	t_xyzpoint		point;
// 	t_xyzpoint		light;
// 	t_sphere		*new;	
	
// 	light = find_light_point_sp(*close_sp, scene);
// 	new = scene->sphere;
// 	scene->sphere = close_sp;
// 	t = check_intersect(scene, light);
// 	point.x = scene->camera->center.x + t * light.x;
// 	point.y = scene->camera->center.y + t * light.y;
// 	point.z = scene->camera->center.z + t * light.z;
// 	scene->sphere = new;
// 	return (point);
// }

// t_xyzpoint		find_light_point_sp(t_sphere close_sp, t_scene *scene)
// {
// 	t_xyzpoint	fin_coord;
	
// 	fin_coord.x = (scene->camera->center.x + scene->camera->orient.x + x - scene->resol.x_size / 2) * weight / scene->resol.x_size;
// 	fin_coord.y = (scene->camera->center.y + scene->camera->orient.y + y - scene->resol.y_size / 2) * hight / scene->resol.y_size;
// 	fin_coord.z = scene->camera->center.z + scene->camera->orient.z;
// 	return (fin_coord);
// }
// // t_xyzpoint	find_center_canvas(t_scene *scene, int x, int y)
// // {
// // 	t_xyzpoint	fin_coord;
// // 	double		weight;
// // 	double		hight;

// // 	weight = find_weight_screen(scene);
// // 	hight = weight * scene->resol.y_size / scene->resol.x_size;
// // 	fin_coord.x = (scene->camera->center.x + scene->camera->orient.x + x - scene->resol.x_size / 2) * weight / scene->resol.x_size;
// // 	fin_coord.y = (scene->camera->center.y + scene->camera->orient.y + y - scene->resol.y_size / 2) * hight / scene->resol.y_size;
// // 	fin_coord.z = scene->camera->center.z + scene->camera->orient.z;
// // 	return (fin_coord);
// // }

// double		find_shadow_t1(t_xyzpoint light, t_xyzpoint ray, t_sphere close_sp)
// {
// 	double 		k1;
// 	double		k2;
// 	double		k3;
// 	double		discriminant;

// 	k1 = scalar(light, light);
// 	k2 = 2 * scalar(ray, light);
// 	k3 = scalar(ray, ray) - pow((close_sp.diametr) / 2, 2);
// 	discriminant = k2 * k2 - 4 * k1 * k3;
// 	if (discriminant < 0)
// 		return (0);
// 	else
// 		return ((-1 * k2 + sqrt(discriminant))/(2 * k1));
// }

// double		find_shadow_t2(t_xyzpoint light, t_xyzpoint ray, t_sphere close_sp)
// {
// 	double 		k1;
// 	double		k2;
// 	double		k3;
// 	double		discriminant;

// 	k1 = scalar(light, light); // возможно будет проблема, т.к. он нормализирован
// 	k2 = 2 * scalar(ray, light);
// 	k3 = scalar(ray, ray) - pow((close_sp.diametr) / 2, 2);
// 	discriminant = k2 * k2 - 4 * k1 * k3;
// 	if (discriminant < 0)
// 		return (0);
// 	else
// 		return ((-1 * k2 - sqrt(discriminant))/(2 * k1));
// }





// x, y  - это изначально координаты полотна, которые начинаются сверху, слева, а тут мы приводим их к другой системе координат
// результат функции ниже - нахождение точки, которая по сути будет точкой 0, 0, 0 на полотне. 


// уравнение плоскости - 
//scene->camera->orient.x * scene->camera->center.x + scene->camera->orient.y * scene->camera->center.y + scene->camera->orient.z * scene->camera->center.z + D = 0;
// нужно через это уравнение плоскости и координаты центра посчитать координаты угла, с помощью разрешения и дальше конвертировать обычный х и игрек в них


// double			check_shadows_sphere(t_sphere *current_sp, t_xyzpoint light, t_scene *scene, double *t)
// {
// 	double		shadow;
// 	double		length;
// 	double		length_cur;

// 	shadow = 0;
// 	while (current_sp)
// 	{
// 		if (t[1] != 1 || current_sp != scene->sphere)
// 		{
// 			length = length_vector(vector_mult(substruct_vector(scene->light->center, current_sp->center), light)) / length_vector(light);
// 			length_cur = sqrt(pow(length_vector(substruct_vector(scene->light->center, current_sp->center)), 2) - pow(length, 2));
// 			if (length <= (current_sp->diametr / 2) && length_vector(light) > length_cur &&
// 			scalar(light, substruct_vector(scene->light->center, current_sp->center)) > 0)
// 				shadow = 1;
// 		}
// 		current_sp = current_sp->next;
// 	}
// 	return (shadow);
// }

// double			check_shadows_plane(t_plane *current_pl, t_xyzpoint light, t_scene *scene, double *t)
// {
// 	double		shadow;
// 	double		d; // перпендикуляр из света к плоскости
// 	double		length;
// 	double		length_cur;

// 	shadow = 0;
// 	while (current_pl)
// 	{
// 		if (t[1] != 2 || current_pl != scene->plane)
// 		{
// 			d = scalar(current_pl->center, current_pl->orient); // тут должен быть минус
// 			d = (scalar(current_pl->orient, scene->light->center) + d) / length_vector(current_pl->orient);
// 			if (d < 0)
// 				d = -d;
// 			length = length_vector(vector_mult(light, mult_num_vect(current_pl->orient, d))) / d;
// 			length_cur = sqrt(pow(length, 2) + pow(d, 2));
// 			if (length_vector(light) > length_cur &&
// 				scalar(light, current_pl->orient) > 0) // тут должно быть меньше 0
// 				shadow = 1;
// 		}
// 		current_pl = current_pl->next;
// 	}
// 	return (shadow);
// }


// ouble			check_shadows_cylin(t_cylin *current_cy, t_xyzpoint light, t_scene *scene, double *t) // функция кривая, надо переписывать. хз как
// {
// 	double		length;
// 	double		length_cur;
	
// 	while (current_cy)
// 	{
// 		if (t[1] != 5 || current_cy != scene->cylin)
// 		{
// 			length = length_vector(vector_mult(light, substruct_vector(scene->light->center, current_cy->center))) / length_vector(light);
// 			if (length == 0)
// 				return (1);
// 			length_cur = sqrt(pow(length_vector(substruct_vector(scene->light->center, current_cy->center)), 2) - pow(length, 2));
// 			if (check_length_cylin(scene, current_cy, length, light) && length_vector(light) > length_cur &&
// 			scalar(light, substruct_vector(scene->light->center, current_cy->center)) != -1)
// 				return (1);
// 		}
// 		current_cy = current_cy->next;
// 	}
// 	return (0);
// }

// double		check_length_cylin(t_scene *scene, t_cylin *current_cy, double length, t_xyzpoint light)
// {
// 	double		angle;
// 	t_xyzpoint	hight;
// 	double		l_temp;

// 	hight = find_point_coordinates(scene->light->center, normalize_vector(light), -length_vector(light));
// 	hight = substruct_vector(hight, current_cy->center);
// 	if (scalar(normalize_vector(hight), normalize_vector(current_cy->orient)) < 0)
// 		current_cy->orient = mult_num_vect(current_cy->orient, -1);
// 	angle = acos(scalar(normalize_vector(hight), normalize_vector(current_cy->orient)));
// 	if (atan(current_cy->diametr/current_cy->lenght) > angle)
// 		l_temp = (current_cy->lenght / 2) / cos(angle);
// 	else
// 		l_temp = (current_cy->diametr / 2) / cos(M_PI/4 - angle);
// 	if (length > l_temp)
// 		return (0);
// 	else
// 		return (1);
// }

// double			check_shadows_cylin(t_cylin *current_cy, t_xyzpoint light, t_scene *scene, double *t) // функция кривая, надо переписывать. хз как
// {
// 	t_cylin		*temp;
// 	t_xyzpoint	canvas;
// 	t_xyzpoint	temp_2;
	
// 	light = mult_num_vect(light, -1);
// 	canvas = find_point_coordinates(scene->light->center, normalize_vector(light), 1);
// 	while (current_cy)
// 	{
// 		if (t[1] != 5 || current_cy != scene->cylin)
// 		{
// 			temp = scene->cylin;
// 			temp_2 = scene->camera->center;
// 			scene->camera->center = scene->light->center;
// 			scene->cylin = current_cy;
// 			if (check_cylin_wall(scene, normalize_vector(light), MAXFLOAT, canvas) > length_vector(light) &&
// 			check_cylin_wall(scene, light, MAXFLOAT, canvas))
// 				{
// 					scene->cylin = temp;
// 					scene->camera->center = temp_2;
// 					return (1);
// 				}
// 			scene->cylin = temp;
// 			scene->camera->center = temp_2;
// 			// length = length_vector(vector_mult(light, substruct_vector(scene->light->center, current_cy->center))) / length_vector(light);
// 			// if (length == 0)
// 			// 	return (1);
// 			// length_cur = sqrt(pow(length_vector(substruct_vector(scene->light->center, current_cy->center)), 2) - pow(length, 2));
// 			// if (check_length_cylin(scene, current_cy, length, light) && length_vector(light) > length_cur &&
// 			// scalar(light, substruct_vector(scene->light->center, current_cy->center)) != -1)
// 			// 	return (1);
// 		}
// 		current_cy = current_cy->next;
// 	}
// 	return (0);
// }

// double		check_length_cylin(t_scene *scene, t_cylin *current_cy, double length, t_xyzpoint light)
// {
// 	double		angle;
// 	t_xyzpoint	hight;
// 	double		l_temp;

// 	hight = find_point_coordinates(scene->light->center, normalize_vector(light), -length_vector(light));
// 	hight = substruct_vector(hight, current_cy->center);
// 	if (scalar(normalize_vector(hight), normalize_vector(current_cy->orient)) < 0)
// 		current_cy->orient = mult_num_vect(current_cy->orient, -1);
// 	angle = acos(scalar(normalize_vector(hight), normalize_vector(current_cy->orient)));
// 	if (atan(current_cy->diametr/current_cy->lenght) > angle)
// 		l_temp = (current_cy->lenght / 2) / cos(angle);
// 	else
// 		l_temp = (current_cy->diametr / 2) / cos(M_PI/4 - angle);
// 	if (length > l_temp)
// 		return (0);
// 	else
// 		return (1);
// }

// int		convert_colour(t_colour colour, double racio)
// {
// 	int		rgb;

// 	rgb = ((int)(colour.r_colour * racio)<<16) | ((int)(colour.g_colour * racio)<<8) | ((int)(colour.b_colour * racio)<<0);
// 	return (rgb);
// }