/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 20:14:22 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/17 00:05:21 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <limits.h>

typedef struct			s_colour
{
	double					r_colour;
	double					g_colour;
	double					b_colour;
}						t_colour;

typedef struct			s_xyzpoint
{
	double				x;
	double				y;
	double				z;
}						t_xyzpoint;

typedef struct			s_resol
{
	int					x_size;
	int					y_size;
	int					count;
}						t_resol;

typedef struct			s_ambi
{
	double				racio;
	t_colour			colour;
	int					count;
}						t_ambi;

typedef struct			s_camera
{
	struct s_camera		*next;
	t_xyzpoint			center;
	t_xyzpoint			orient;
	double				fov;
	int					count;
}						t_camera;

typedef struct			s_light
{
	struct s_light		*next;
	t_xyzpoint			center;
	double				racio;
	t_colour			colour;
	int					count;
}						t_light;

typedef struct			s_sphere
{
	struct s_sphere		*next;
	t_xyzpoint			center;
	double				diametr;
	t_colour			colour;
	int					count;
}						t_sphere;

typedef struct			s_plane
{
	struct s_plane		*next;
	t_xyzpoint			center;
	t_xyzpoint			orient;
	t_colour			colour;
	int					count;
}						t_plane;

typedef struct			s_square
{
	struct s_square		*next;
	t_xyzpoint			center;
	t_xyzpoint			orient;
	double				lenght;
	t_colour			colour;
	int					count;
}						t_square;

typedef struct			s_cylin
{
	struct s_cylin		*next;
	t_xyzpoint			center;
	t_xyzpoint			orient;
	t_xyzpoint			normal;
	double				diametr;
	double				lenght;
	t_colour			colour;
	int					count;
}						t_cylin;

typedef struct			s_triangle
{
	struct s_triangle	*next;
	t_xyzpoint			angle_one;
	t_xyzpoint			angle_two;
	t_xyzpoint			angle_three;
	t_xyzpoint			normal;
	t_colour			colour;
	int					count;
}						t_triangle;

typedef struct			s_scene
{
	t_resol				resol;
	t_ambi				ambi;
	t_camera			*camera;
	t_light				*light;
	t_sphere			*sphere;
	t_plane				*plane;
	t_square			*square;
	t_cylin				*cylin;
	t_triangle			*triangle;
	int					mistake;
	double				**points;
}						t_scene;

t_sphere				*g_sphere;
t_plane					*g_plane;
t_triangle				*g_triangle;
t_square				*g_square;
t_cylin					*g_cylin;

int						minirt(int argc, char **argv);
void					parser(t_scene *scene, int fd);
int						pars_line(char *line, t_scene *scene);
int						pars_triangle(char *line, t_scene *scene);
int						pars_triangle_list(char *line, t_scene *scene);
int						pars_sphere(char *line, t_scene *scene);
int						pars_sphere_list(char *line, t_scene *scene);
int						pars_square(char *line, t_scene *scene);
int						pars_square_list(char *line, t_scene *scene);
int						pars_cylin(char *line, t_scene *scene);
int						pars_cylin_list(char *line, t_scene *scene);
int						pars_plane(char *line, t_scene *scene);
int						pars_plane_list(char *line, t_scene *scene);
int						pars_resol(char *line, t_scene *scene);
int						pars_ambient(char *line, t_scene *scene);
int						pars_light(char *line, t_scene *scene);
int						pars_light_list(char *line, t_scene *scene);
int						pars_camera(char *line, t_scene *scene);
int						pars_camera_list(char *line, t_scene *scene);
t_colour				pars_colour(char **line, t_scene *scene);
int						pars_one_colour(char **line);
t_xyzpoint				pars_center(char **line, t_scene *scene);
t_xyzpoint				pars_orient(char **line, t_scene *scene);
double					pars_double(double x, char **line);
void					init_scene(t_scene *scene);
t_triangle				*t_init(void);
t_cylin					*cy_init(void);
t_square				*sq_init(void);
t_plane					*p_init(void);
t_sphere				*sp_init(void);
t_light					*l_init(void);
t_camera				*c_init(void);
t_ambi					a_init(void);
t_resol					r_init(void);
t_xyzpoint				init_orient(void);
t_colour				init_colour(void);
t_xyzpoint				init_center(void);
void					t_init_points(t_scene *scene);
void					start_work(t_scene *scene);
int						convert_colour(t_colour colour, double racio);
void					render(t_scene *scene, void *mlx_ptr, void *win_ptr);
int						sph_ray_intersect(t_scene *scene);
// void					draw_sphere(t_scene *scene, void *mlx_ptr, void *win_ptr);
int						free_struct(t_scene *scene);
int						ft_isdigit(int sym);
int						free_struct(t_scene *scene);
double 					scalar(t_xyzpoint vector_1, t_xyzpoint vector_2);
t_xyzpoint				vector_mult(t_xyzpoint vector_1, t_xyzpoint vector_2);
double					length_vector(t_xyzpoint vector);
t_xyzpoint				normalize_vector(t_xyzpoint vect);
void					render(t_scene *scene, void *mlx_ptr, void *win_ptr);
void					draw_sphere(t_scene *scene, void *mlx_ptr, void *win_ptr);
double					check_sphere(t_scene *scene, int x, int y);
t_xyzpoint				find_center_canvas(t_scene *scene, int x, int y);
double					find_first_t(t_scene *scene, t_xyzpoint canvas);
double					find_second_t(t_scene *scene, t_xyzpoint canvas);
double					find_weight_screen(t_scene *scene);
double					check_light(t_scene *scene, int x, int y, double *t);
t_xyzpoint				substruct_vector(t_xyzpoint vect_1, t_xyzpoint vect_2);
t_colour				find_colour(t_scene *scene, int x, int y, double *t);
int						convert_colour_2(t_colour colour, t_colour intens);
double					check_shadows(t_xyzpoint light, t_scene *scene);
// double					find_shadow_t1(t_xyzpoint light, t_xyzpoint ray, t_sphere close_sp);
// double					find_shadow_t2(t_xyzpoint light, t_xyzpoint ray, t_sphere close_sp);
// t_xyzpoint				find_point(t_scene *scene, t_sphere *close_sp);
// t_xyzpoint				find_light_point_sp(t_sphere close_sp, t_scene *scene);
void					draw_plane(t_scene *scene, void *mlx_ptr, void *win_ptr);
double					check_plane(t_scene *scene, int x, int y);
t_colour				find_colour_2(t_scene *scene, int x, int y, double *t);
double					check_light_2(t_scene *scene, int x, int y, double *t);
double					check_shadows_2(t_xyzpoint light, t_scene *scene);
void					draw_triangle(t_scene *scene, void *mlx_ptr, void *win_ptr);
double					check_triangle(t_scene *scene, int x, int y);
int						check_inside_triangle(t_xyzpoint cam, t_triangle *triangle, t_xyzpoint ray, double t);
void					draw_square(t_scene *scene, void *mlx_ptr, void *win_ptr);
double					check_square(t_scene *scene, int x, int y);
// int						check_inside_square(t_scene *scene, t_xyzpoint ray, double t);
int						check_inside_square(t_xyzpoint cam, t_square *square, t_xyzpoint ray, double t);
void					draw_cylin(t_scene *scene, void *mlx_ptr, void *win_ptr);
double					check_cylin(t_scene *scene, int x, int y);
double					check_cylin_wall(t_scene *scene, t_xyzpoint ray, double t, t_xyzpoint canvas);
double					find_t1_cyl(t_xyzpoint canvas, t_scene *scene, t_xyzpoint ray);
double					find_t2_cyl(t_xyzpoint canvas, t_scene *scene, t_xyzpoint ray);
double					find_t3_cyl(t_xyzpoint canvas, t_scene *scene, t_xyzpoint ray);
double					find_t4_cyl(t_xyzpoint canvas, t_scene *scene, t_xyzpoint ray);
t_xyzpoint				find_point_coordinates(t_xyzpoint cntr, t_xyzpoint orient, double s);
double					find_k_1_3(t_xyzpoint vect, t_scene *scene);
double					find_k_2(t_xyzpoint vect_1, t_xyzpoint vect_2, t_scene *scene);
t_xyzpoint				find_figure_center(t_scene *scene, double *t, t_xyzpoint canvas);
t_xyzpoint				find_cylin_normal(t_scene *scene, double *t, t_xyzpoint canvas);
double					check_shadows_all(t_xyzpoint light, t_scene *scene, double *t);
double					check_shadows_sphere(t_sphere *current_sp, t_xyzpoint light, t_scene *scene, double *t);
double					check_shadows_plane(t_plane *current_pl, t_xyzpoint light, t_scene *scene, double *t);
double					check_shadows_triangle(t_triangle *current_tr, t_xyzpoint light, t_scene *scene, double *t);
double					check_shadows_square(t_square *current_sq, t_xyzpoint light, t_scene *scene, double *t);
double					check_shadows_cylin(t_cylin *current_cy, t_xyzpoint light, t_scene *scene, double *t);
double					check_length_cylin(t_scene *scene, t_cylin *cylin, double length, t_xyzpoint light);
t_xyzpoint				mult_num_vect(t_xyzpoint vector, double num);
t_xyzpoint				normalize_orient(t_xyzpoint xyz, t_xyzpoint orient, t_xyzpoint camera);
t_xyzpoint				normalize_orient_perp(t_xyzpoint xyz, t_xyzpoint orient, t_xyzpoint camera);
t_xyzpoint				find_cylin_normal_2(t_cylin *cylin, t_scene *scene, double t, t_xyzpoint ray);

// int     				find_min_x_sp(t_scene *scene);
// int     				find_min_y_sp(t_scene *scene);
// int     				find_max_x_sp(t_scene *scene);
// int     				find_max_y_sp(t_scene *scene);

#endif
