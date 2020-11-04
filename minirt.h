/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 20:14:22 by scopycat          #+#    #+#             */
/*   Updated: 2020/11/03 15:23:33 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <pthread.h>
# include <errno.h>
# include <math.h>
# include <limits.h>

typedef struct			s_index
{
	double				t;
	int					i_f;
	int					i_f_n;
	int					ind_l_n;
	int					count;
}						t_index;

typedef struct			s_colour
{
	double				r_colour;
	double				g_colour;
	double				b_colour;
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
	t_xyzpoint			ox;
	t_xyzpoint			oy;
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

typedef	struct			s_angles
{
	t_xyzpoint			a;
	t_xyzpoint			b;
	t_xyzpoint			c;
	t_xyzpoint			d;
}						t_angles;

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
	double				save;
	char				*scene_name;
}						t_scene;

typedef	struct			s_mlx
{
	void				*m_ptr;
	void				*w_ptr;
	void				*img;
	char				*addr;
	int					bpp;
	int					length;
	int					end;
}						t_mlx;

typedef struct			s_matrix
{
	t_xyzpoint			str_1;
	t_xyzpoint			str_2;
	t_xyzpoint			str_3;
}						t_matrix;

typedef struct			s_file_header
{
	short				signature;
	int					file_size;
	int					reserved;
	int					offset_to_pix;
}						t_file_header;

typedef struct			s_bmp_info
{
	int					headersize;
	int					weight;
	int					hight;
	short				plane;
	short				bpp;
	int					compress;
	int					imagesize;
	int					bpmx;
	int					bpmy;
	int					colour;
	int					colout_imp;
}						t_bmp_info;

t_scene					*g_scene;
t_scene					*g_scene_copy;
t_camera				*g_camera;
t_mlx					g_mlx;
t_xyzpoint				g_ox;
t_xyzpoint				g_oy;

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
t_mlx					init_mlx(void);
void					t_init_points(t_scene *scene);
void					start_work(t_scene *scene);
void					check_resol(t_scene *scene);
void					prerender(t_scene *scene, t_mlx *mlx);
void					*render(void *x);
void					render_threads(t_scene *scene, t_mlx *mlx, int x);
void					fill_ambient(t_scene *scene, t_mlx *mlx, int x);
void					my_mlx_pixel_put(t_mlx *mlx, int x, int y, int colour);
void					redraw_pic(t_scene *scene);
int						key_pressed(int key_code, t_scene *scene);
int						mouse_pressed(t_scene *scene);
void					change_colours(t_scene *scene, int keycode);
void					change_colours_figures(t_scene *scene, int keycode);
void					change_colours_sphere(t_scene *scene, int keycode);
void					change_colours_plane(t_scene *scene, int keycode);
void					change_colours_triangle(t_scene *scene, int keycode);
void					change_colours_square(t_scene *scene, int keycode);
void					change_colours_cylin(t_scene *scene, int keycode);
void					rotate_cam(t_scene *scene);
int						free_struct(t_scene *scene);
void					free_camera(t_scene *scene);
void					free_light(t_scene *scene);
void					free_sphere(t_scene *scene);
void					free_plane(t_scene *scene);
void					free_triangle(t_scene *scene);
void					free_square(t_scene *scene);
void					free_cylin(t_scene *scene);
void					free_points(t_scene *scene);
double					scalar(t_xyzpoint vector_1, t_xyzpoint vector_2);
t_xyzpoint				vector_mult(t_xyzpoint vector_1, t_xyzpoint vector_2);
double					length_vector(t_xyzpoint vector);
t_xyzpoint				normalize_vector(t_xyzpoint vect);
t_xyzpoint				vector_div(t_xyzpoint vect, double num);
t_xyzpoint				mult_num_vect(t_xyzpoint vector, double num);
t_xyzpoint				sum_vect(t_xyzpoint vect_1, t_xyzpoint vect_2);
void					draw_sphere(t_scene *scene, t_mlx *mlx, int x, int i);
void					draw_sphere_util(t_scene *scene, t_mlx *mlx, int x, \
							t_index sp);
double					check_sphere(t_scene *scene, int x, int y, int i);
t_xyzpoint				find_center_canvas(t_scene *scene, int x, int y);
double					find_first_t(t_scene *scene, t_xyzpoint canvas, int i);
double					find_second_t(t_scene *scene, t_xyzpoint canvas, int i);
double					find_weight_screen(t_scene *scene);
double					check_light(t_scene *scene, int x, int y, t_index sp);
t_xyzpoint				substruct_vector(t_xyzpoint vect_1, t_xyzpoint vect_2);
t_colour				find_colour(t_scene *scene, int x, int y, t_index sp);
int						convert_colour(t_colour colour, t_colour intens);
int						convert_colour_ambi(t_colour colour, double racio);
double					check_shadows(t_xyzpoint light, t_scene *scene);
void					check_cam(t_scene *scene);
void					change_coordinates_all(t_scene *scene, t_matrix matrix);
t_matrix				rotate_matrix(t_scene *scene);
void					change_light_coor(t_scene *scene, t_matrix matrix);
void					change_sphere_coor(t_scene *scene, t_matrix matrix);
void					change_plane_coor(t_scene *scene, t_matrix matrix);
void					change_triangle_coor(t_scene *scene, t_matrix matrix);
void					change_square_coor(t_scene *scene, t_matrix matrix);
void					change_cylin_coor(t_scene *scene, t_matrix matrix);
t_xyzpoint				mult_point_matrix(t_xyzpoint point, t_matrix matrix);
void					draw_plane(t_scene *scene, t_mlx *mlx, int x, int i);
void					draw_plane_util(t_scene *scene, t_mlx *mlx, int x, \
							t_index pl);
double					check_plane(t_scene *scene, int x, int y, int i);
t_colour				find_colour_2(t_scene *scene, int x, int y, \
							t_index fig);
double					check_light_2(t_scene *scene, int x, int y, \
							t_index fig);
double					check_shadows_2(t_xyzpoint light, t_scene *scene);
void					draw_triangle(t_scene *scene, t_mlx *mlx, int x, int i);
void					draw_triangle_util(t_scene *scene, t_mlx *mlx, int x, \
							t_index tr);
double					find_t_triangle(t_scene *scene, t_xyzpoint canvas, \
							t_triangle *tr, t_xyzpoint normal);
double					check_triangle(t_scene *scene, int x, int y, int i);
int						check_inside_triangle(t_xyzpoint cam, \
							t_triangle *triangle, t_xyzpoint ray, double t);
void					draw_square(t_scene *scene, t_mlx *mlx, int x, int i);
void					draw_square_util(t_scene *scene, t_mlx *mlx, int x, \
							t_index sq);
double					check_square(t_scene *scene, int x, int y, int i);
int						check_inside_square(t_xyzpoint cam, t_square *square, \
							t_xyzpoint ray, double t);
t_xyzpoint				find_first_angle(t_square *square);
void					draw_cylin(t_scene *scene, t_mlx *mlx, int x, int i);
void					draw_cylin_util(t_scene *scene, t_mlx *mlx, int x, \
							t_index cy);
double					check_cylin(t_scene *scene, int x, int y, int i);
double					check_cylin_wall(t_cylin *cylin, t_xyzpoint ray, \
							double t, t_xyzpoint start);
double					find_t1_cyl(t_xyzpoint start, t_cylin *cylin, \
							t_xyzpoint ray);
double					find_t2_cyl(t_xyzpoint start, t_cylin *cylin, \
							t_xyzpoint ray);
double					find_t3_cyl(t_xyzpoint start, t_cylin *cylin, \
							t_xyzpoint ray);
double					find_t4_cyl(t_xyzpoint start, t_cylin *cylin, \
							t_xyzpoint ray);
t_xyzpoint				find_point_coordinates(t_xyzpoint cntr, \
							t_xyzpoint orient, double s);
double					find_k_1_3(t_xyzpoint vect, t_xyzpoint orient);
double					find_k_2(t_xyzpoint vect_1, t_xyzpoint vect_2, \
							t_xyzpoint orient);
t_xyzpoint				find_figure_center(t_scene *scene, t_index fig, \
							t_xyzpoint canvas);
t_xyzpoint				find_sphere_point(t_scene *scene, t_index fig);
t_xyzpoint				find_plane_point(t_scene *scene, t_index fig);
t_xyzpoint				find_triangle_point(t_scene *scene, t_index fig);
t_xyzpoint				find_square_point(t_scene *scene, t_index fig);
t_xyzpoint				find_cylin_point(t_scene *scene, t_index fig, \
							t_xyzpoint canvas);
double					check_shadows_all(t_xyzpoint light, t_scene *scene, \
							t_index fig);
double					check_shadows_sphere(t_sphere *current_sp, \
						t_xyzpoint light, t_scene *scene, t_index fig);
double					check_shadows_plane(t_plane *current_pl, \
							t_xyzpoint light, t_scene *scene, t_index fig);
double					check_shadows_triangle(t_triangle *current_tr, \
							t_xyzpoint light, t_scene *scene, t_index fig);
double					check_shadows_square(t_square *current_sq, \
							t_xyzpoint light, t_scene *scene, t_index fig);
double					check_shadows_cylin(t_cylin *current_cy, \
							t_xyzpoint light, t_scene *scene, t_index fig);
double					check_length_cylin(t_scene *scene, t_cylin *cylin, \
							double length, t_xyzpoint light);
t_xyzpoint				normalize_orient(t_xyzpoint xyz, t_xyzpoint orient, \
							t_xyzpoint camera);
t_xyzpoint				normalize_orient_perp(t_xyzpoint xyz, \
							t_xyzpoint orient, t_xyzpoint camera);
t_xyzpoint				find_cylin_normal(t_cylin *cylin, t_xyzpoint camera, \
							double t, t_xyzpoint ray);
double					length_to_pl_point(t_xyzpoint start, t_xyzpoint \
							normal, t_xyzpoint pl_point, t_xyzpoint vect);
double					check_save(char *frase);
void					reinit_points(t_scene *scene);
void					put_image_bmp(t_scene *scene);
t_xyzpoint				vector_div(t_xyzpoint vect, double num);
void					put_image_bmp(t_scene *scene);
void					fill_bmp(t_bmp_info bmpi, t_file_header header, \
							char *name, t_scene *scene);
int						fill_pixels(int	fd, int x, int y);
int						ft_strncmp(const char *str1, const char *str2, \
							size_t len);
int						ft_isdigit(int sym);

#endif
