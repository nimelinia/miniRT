/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_mlx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 21:14:12 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/18 00:47:05 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft/libft.h"
#include "get_next_line.h"
#include "minilibx_mms/mlx.h"

void	start_work(t_scene *scene)
{
	void	*mlx_ptr;
	void	*win_ptr;
	// int		x = 0;
	// int		y = 0;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, scene->resol.x_size, scene->resol.y_size, "miniRT");
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
	render(scene, mlx_ptr, win_ptr);
	mlx_hook(win_ptr, 17, 1 << 17, free_struct, scene);
	mlx_loop(mlx_ptr);
	
}

int		convert_colour(t_colour colour, double racio)
{
	int		rgb;

	rgb = ((int)(colour.r_colour * racio)<<16) | ((int)(colour.g_colour * racio)<<8) | ((int)(colour.b_colour * racio)<<0);
	return (rgb);
}

int		convert_colour_2(t_colour colour, t_colour intens)
{
	int		rgb;

	colour.r_colour = colour.r_colour * intens.r_colour / 255;
	colour.g_colour = colour.g_colour * intens.g_colour / 255;
	colour.b_colour = colour.b_colour * intens.b_colour / 255;
	if (colour.r_colour > 255)
		colour.r_colour = 255;
	if (colour.g_colour > 255)
		colour.g_colour = 255;
	if (colour.b_colour > 255)
		colour.b_colour = 255;	
	rgb = ((int)(colour.r_colour)<<16) | ((int)(colour.g_colour)<<8) | ((int)(colour.b_colour)<<0);
	return (rgb);
}

void	render(t_scene *scene, void *mlx_ptr, void *win_ptr)
{
	g_sphere = scene->sphere; // перенести в другую функцию и сделать глобалки по всем
	g_plane = scene->plane;
	g_triangle = scene->triangle;
	g_square = scene->square;
	g_cylin = scene->cylin;
	while (scene->sphere) // переделать на переключение камер
	{
		draw_sphere(scene, mlx_ptr, win_ptr);
		scene->sphere = scene->sphere->next;
	}
	scene->sphere = g_sphere; // перенести в другую функцию
	while (scene->plane)
	{
		draw_plane(scene, mlx_ptr, win_ptr);
		scene->plane = scene->plane->next;
	}
	scene->plane = g_plane;
	while (scene->triangle)
	{
		draw_triangle(scene, mlx_ptr, win_ptr);
		scene->triangle = scene->triangle->next;
	}
	scene->triangle = g_triangle;
	while (scene->square)
	{
		draw_square(scene, mlx_ptr, win_ptr);
		scene->square = scene->square->next;
	}
	scene->square = g_square;
	while (scene->cylin)
	{
		draw_cylin(scene, mlx_ptr, win_ptr);
		scene->cylin = scene->cylin->next;
	}
	scene->cylin = g_cylin;
}

t_xyzpoint	find_point_coordinates(t_xyzpoint cntr, t_xyzpoint orient, double s)
{
	t_xyzpoint	result;

	result.x = cntr.x + orient.x * s;
	result.y = cntr.y + orient.y * s;
	result.z = cntr.z + orient.z * s;
	return (result);
}




t_colour	find_colour(t_scene *scene, int x, int y, double *t)
{
	double		light;
	t_light		*new;
	t_colour	intens;
	
	new = scene->light;
	intens = init_colour();
	while (scene->light)
	{
		light = check_light(scene, x, y, t);
		intens.r_colour += light * scene->light->colour.r_colour;
		intens.g_colour += light * scene->light->colour.g_colour;
		intens.b_colour += light * scene->light->colour.b_colour;
		scene->light = scene->light->next;
	}
	intens.r_colour += scene->ambi.racio * scene->ambi.colour.r_colour;
	intens.g_colour += scene->ambi.racio * scene->ambi.colour.g_colour;
	intens.b_colour += scene->ambi.racio * scene->ambi.colour.b_colour;
	scene->light = new;
	return (intens);
}

t_colour	find_colour_2(t_scene *scene, int x, int y, double *t)
{
	double		light;
	t_light		*new;
	t_colour	intens;
	
	new = scene->light;
	intens = init_colour();
	while (scene->light)
	{
		light = check_light_2(scene, x, y, t);
		intens.r_colour += light * scene->light->colour.r_colour;
		intens.g_colour += light * scene->light->colour.g_colour;
		intens.b_colour += light * scene->light->colour.b_colour;
		scene->light = scene->light->next;
	}
	intens.r_colour += scene->ambi.racio * scene->ambi.colour.r_colour;
	intens.g_colour += scene->ambi.racio * scene->ambi.colour.g_colour;
	intens.b_colour += scene->ambi.racio * scene->ambi.colour.b_colour;
	scene->light = new;
	return (intens);
}

double	check_light_2(t_scene *scene, int x, int y, double *t)
{
	t_xyzpoint	point;
	t_xyzpoint	figure_normal;
	t_xyzpoint	light;
	double		res;
	

	res = 0.0;
	figure_normal = find_figure_center(scene, t, find_center_canvas(scene, x, y));
	// canvas = normalize_vector(canvas);
	point = find_point_coordinates(scene->camera->center, find_center_canvas(scene, x, y), t[0]); //точка на плоскости
	light = substruct_vector(scene->light->center, point);
	light = normalize_vector(light);
	// if (scalar(figure_normal, light) < 0) //если косинус меньше 0, то значит угол тупой
	// 	res = -(scene->light->racio * scalar(figure_normal, light));
	if (scalar(figure_normal, light) > 0) //вектор нормали смотрит в сторону камеры, если вектор из точки
		res = (scene->light->racio * scalar(figure_normal, light)); // в источник света смотрит туда же, то она этим светом освещена
	// if (check_shadows_2(substruct_vector(scene->light->center, point), scene))
	// if (check_shadows_all(substruct_vector(point, scene->light->center), scene, t))
	if (check_shadows_all(substruct_vector(scene->light->center, point), scene, t))
		res = 0.0;
	return (res);
}

double	check_light(t_scene *scene, int x, int y, double *t)
{
	t_xyzpoint	point;
	t_xyzpoint	figure_point;
	t_xyzpoint	normal;
	t_xyzpoint	light;
	double		res;
	

	res = 0.0;
	figure_point = find_figure_center(scene, t, find_center_canvas(scene, x, y));
	point = find_point_coordinates(scene->camera->center, find_center_canvas(scene, x, y), t[0]);
	normal = substruct_vector(point, figure_point);
	normal = normalize_vector(normal);
	light = substruct_vector(scene->light->center, point);
	light = normalize_vector(light);
	if (scalar(normal, light) > 0)
		res = (scene->light->racio * scalar(normal, light));
	// if (check_shadows(substruct_vector(scene->light->center, point), scene))
	// if (check_shadows_all(substruct_vector(point, scene->light->center), scene, t))
	if (check_shadows_all(substruct_vector(scene->light->center, point), scene, t))
		res = 0.0;
	return (res);
}

t_xyzpoint		find_figure_center(t_scene *scene, double *t, t_xyzpoint canvas)
{
	t_xyzpoint	point;

	if (t[1] == 1)
		point = scene->sphere->center;
	else if (t[1] == 2)
		point = scene->plane->orient;
		// point = mult_num_vect(scene->plane->orient, -1);
	else if (t[1] == 3)
		// point = scene->triangle->angle_one;
		// point = normalize_vector(vector_mult(substruct_vector(scene->triangle->angle_one, \
		// scene->triangle->angle_two), substruct_vector(\
		// scene->triangle->angle_three, scene->triangle->angle_two)));
		point = scene->triangle->normal;
		// point = normalize_orient(scene->triangle->angle_one, scene->triangle->normal, scene->light->center);
	else if (t[1] == 4)
		point = scene->square->orient;
	else if (t[1] == 5)
		point = scene->cylin->normal;
		// point = find_cylin_normal(scene, t, canvas);
	else
	{
		point.x = canvas.x * 0;
		point.y = 0;
		point.z = 0;
	}
	return (point);
}

t_xyzpoint		find_cylin_normal(t_scene *scene, double *t, t_xyzpoint canvas)
{
	t_xyzpoint	point;
	t_xyzpoint	ray;
	t_xyzpoint	normal;
	t_xyzpoint	result;
	double		d;

	ray = normalize_vector(substruct_vector(canvas, scene->camera->center));
	point = find_point_coordinates(scene->camera->center, ray, t[0]);
	normal = normalize_vector(scene->cylin->orient);
	d = scalar(substruct_vector(point, scene->cylin->center), normal);
	result = find_point_coordinates(scene->cylin->center, normal, d);
	result = substruct_vector(point, result);
	// result = normalize_orient(point, result, scene->camera->center);
	scene->cylin->normal = result;
	
	return (result);
}



double			check_shadows_all(t_xyzpoint light, t_scene *scene, double *t)
{
	t_sphere	*current_sp;
	t_plane		*current_pl;
	t_triangle	*current_tr;
	t_square	*current_sq;
	t_cylin		*current_cy;

	current_sp = g_sphere;
	current_pl = g_plane;
	current_tr = g_triangle;
	current_sq = g_square;
	current_cy = g_cylin;
	if (check_shadows_sphere(current_sp, light, scene, t))
		return (1);
	if (check_shadows_plane(current_pl, light, scene, t))
		return (1);
	if (check_shadows_triangle(current_tr, light, scene, t))
		return (1);
	if (check_shadows_square(current_sq, light, scene, t))
		return (1);
	if (check_shadows_cylin(current_cy, light, scene, t))
		return (1);
	else
		return (0);
}

double			check_shadows_sphere(t_sphere *current_sp, t_xyzpoint light, t_scene *scene, double *t)
{
	double		length;
	double		length_cur;

	while (current_sp)
	{
		if (t[1] != 1 || current_sp != scene->sphere)
		{
			length = length_vector(vector_mult(light, substruct_vector(scene->light->center, current_sp->center))) / length_vector(light);
			length_cur = sqrt(pow(length_vector(substruct_vector(scene->light->center, current_sp->center)), 2) - pow(length, 2));
			if (length <= (current_sp->diametr / 2) && length_vector(light) > length_cur &&
			scalar(light, substruct_vector(scene->light->center, current_sp->center)) > 0)
				return (1);
		}
		current_sp = current_sp->next;
	}
	return (0);
}

double			check_shadows_plane(t_plane *current_pl, t_xyzpoint light, t_scene *scene, double *t) // функция кривая, надо переписывать. хз как
{
	double		d; // перпендикуляр из света к плоскости
	double		length;
	// double		length_cur;

	// light = mult_num_vect(light, -1);
	while (current_pl)
	{
		if (t[1] != 2 || current_pl != scene->plane)
		{	
			current_pl->orient = normalize_orient(current_pl->center, current_pl->orient, scene->camera->center);
			d = -scalar(current_pl->center, current_pl->orient);
			length = -(d + scalar(current_pl->orient, scene->light->center)) / \
			scalar(current_pl->orient, mult_num_vect(light, -1));
			if (length_vector(light) > length && scalar(normalize_vector(light), current_pl->orient) < 0 && length > 0)
			// if (length_vector(light) > length && scalar(normalize_vector(light), normalize_vector(current_pl->orient)) < 0)
				return (1);
			// d = -scalar(current_pl->center, current_pl->orient); // тут должен быть минус
			// d = -(scalar(current_pl->orient, scene->light->center) + d) / length_vector(current_pl->orient);
			// length = length_vector(vector_mult(mult_num_vect(normalize_vector(current_pl->orient), d), light)) / length_vector(light);
			// length_cur = d / sin(acos(length / d));
			// if (length_vector(light) > length_cur && scalar(normalize_vector(light), current_pl->orient) < 0 && length_cur > 0) // тут должно быть меньше 0
			// 	return (1);
		}
		current_pl = current_pl->next;
	}
	return (0);
}


double			check_shadows_triangle(t_triangle *current_tr, t_xyzpoint light, t_scene *scene, double *t) // функция кривая, надо переписывать. хз как
{
	double		d; // перпендикуляр из света к плоскости
	double		length;
	t_xyzpoint	antilight;

	antilight = normalize_vector(mult_num_vect(light, -1));
	while (current_tr)
	{
		if (t[1] != 3 || current_tr != scene->triangle)
		{
			current_tr->normal = vector_mult(substruct_vector(current_tr->angle_two, \
				current_tr->angle_one), substruct_vector(current_tr->angle_three, current_tr->angle_one));
			current_tr->normal = normalize_orient(current_tr->angle_one, current_tr->normal, scene->camera->center);
			d = -scalar(current_tr->angle_one, current_tr->normal);
			length = -(d + scalar(current_tr->normal, scene->light->center)) / \
			scalar(current_tr->normal, antilight);
			if (check_inside_triangle(scene->light->center, current_tr, antilight, length) && 
				(scalar(normalize_vector(light), current_tr->normal) != 0 || length > 0) && length < length_vector(light)  ) // здесь свет - это из точки на свет
				 //scalar(normalize_vector(light), current_tr->normal) < 0
				return (1);

			// current_tr->normal = vector_mult(substruct_vector(current_tr->angle_two, \
			// 	current_tr->angle_one), substruct_vector(current_tr->angle_three, current_tr->angle_one));
			// current_tr->normal = normalize_orient(current_tr->angle_one, current_tr->normal, scene->camera->center);
			// length = (scalar(current_tr->angle_two, current_tr->normal) - scalar(current_tr->normal, \
			// 	scene->light->center)) / scalar(current_tr->normal, antilight);
			// if (check_inside_triangle(scene->light->center, current_tr, antilight, length) && 
			// 	scalar(normalize_vector(light), current_tr->normal) != 0 && length > 0 && length < length_vector(light)) // здесь свет - это из точки на свет
			// 	return (1);
		}
		current_tr = current_tr->next;
	}
	return (0);
}

double			check_shadows_square(t_square *current_sq, t_xyzpoint light, t_scene *scene, double *t) // функция кривая, надо переписывать. хз как
{
	// double		d; // перпендикуляр из света к плоскости
	double		length;
	t_xyzpoint	antilight;

	antilight = normalize_vector(mult_num_vect(light, -1));
	while (current_sq)
	{
		if (t[1] != 4 || current_sq != scene->square)
		{	
			// current_sq->orient = normalize_orient(current_sq->center, current_sq->orient, scene->camera->center);
			// // current_sq->orient = mult_num_vect(current_sq->orient, -1);
			// // d = -scalar(current_sq->center, current_sq->orient);
			// // length = -(d + scalar(current_sq->orient, scene->light->center) / \
			// // scalar(current_sq->orient, antilight));
			// length = (scalar(current_sq->center, current_sq->orient) - \
			// 	scalar(current_sq->orient,  scene->camera->center)) / \
			// 	scalar(current_sq->orient, antilight);
			// if (check_inside_square(scene->light->center, current_sq, antilight, length) && 
			// 	scalar(normalize_vector(light), current_sq->orient) != 0 && length > 0 && length < length_vector(light))//mult_num_vect(current_sq->orient, -1)) > 0) // здесь свет - это из точки на свет
			// 	return (1);
			
			current_sq->orient = normalize_orient(current_sq->center, current_sq->orient, scene->camera->center);
			// d = -scalar(current_sq->center, current_sq->orient);
			// length = fabs((d + scalar(current_sq->orient, scene->light->center)) / \
			// scalar(current_sq->orient, normalize_vector(light)));
			length = (scalar(current_sq->center, current_sq->orient) - \
				scalar(current_sq->orient,  scene->camera->center)) / \
				scalar(current_sq->orient, normalize_vector(light));
			if (check_inside_square(scene->light->center, current_sq, normalize_vector(light), length) && 
				scalar(light, current_sq->orient) > 0 && length > 0 && length < length_vector(light))//mult_num_vect(current_sq->orient, -1)) > 0) // здесь свет - это из точки на свет
				return (1);
		}
		current_sq = current_sq->next;
	}
	return (0);
}

double			check_shadows_cylin(t_cylin *current_cy, t_xyzpoint light, t_scene *scene, double *t) // функция кривая, надо переписывать. хз как
{
	t_cylin		*temp;
	t_xyzpoint	canvas;
	t_xyzpoint	temp_2;
	
	light = mult_num_vect(light, -1);
	canvas = find_point_coordinates(scene->light->center, normalize_vector(light), -0.1);
	while (current_cy)
	{
		if (t[1] != 5 || current_cy != scene->cylin)
		{
			temp = scene->cylin;
			temp_2 = scene->camera->center;
			scene->camera->center = scene->light->center;
			scene->cylin = current_cy;
			if (check_cylin_wall(scene, normalize_vector(light), MAXFLOAT, canvas) < length_vector(light) &&
			check_cylin_wall(scene, normalize_vector(light), MAXFLOAT, canvas))
				{
					scene->cylin = temp;
					scene->camera->center = temp_2;
					return (1);
				}
			scene->cylin = temp;
			scene->camera->center = temp_2;
			// length = length_vector(vector_mult(light, substruct_vector(scene->light->center, current_cy->center))) / length_vector(light);
			// if (length == 0)
			// 	return (1);
			// length_cur = sqrt(pow(length_vector(substruct_vector(scene->light->center, current_cy->center)), 2) - pow(length, 2));
			// if (check_length_cylin(scene, current_cy, length, light) && length_vector(light) > length_cur &&
			// scalar(light, substruct_vector(scene->light->center, current_cy->center)) != -1)
			// 	return (1);
		}
		current_cy = current_cy->next;
	}
	return (0);
}

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

	weight = find_weight_screen(scene);
	hight = weight * scene->resol.y_size / scene->resol.x_size;
	fin_coord.x = (scene->camera->center.x + scene->camera->orient.x + x - scene->resol.x_size / 2) * weight / scene->resol.x_size;
	fin_coord.y = (scene->camera->center.y + scene->camera->orient.y + y - scene->resol.y_size / 2) * hight / scene->resol.y_size;
	fin_coord.z = scene->camera->center.z + scene->camera->orient.z;
	return (fin_coord);
}

double	find_weight_screen(t_scene *scene)
{
	double	a;
	double	b;
	
	a = length_vector(scene->camera->orient);
	b = a * tan(scene->camera->fov * M_PI/ 360);
	return (b * 2);
}

int		free_struct(t_scene *scene)
{
	if (scene->camera)
		free(scene->camera);
	exit (0);
}


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