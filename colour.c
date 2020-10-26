/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:32:13 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/26 18:38:23 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

int		convert_colour(t_colour colour, t_colour intens)
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

t_colour	find_colour(t_scene *scene, int x, int y, t_index sp)
{
	double		light;
	t_light		*new_l;
	t_colour	intens;
	
	new_l = scene->light;
	intens = init_colour();
	while (new_l)
	{
		light = check_light(scene, x, y, sp);
		intens.r_colour += light * new_l->colour.r_colour;
		intens.g_colour += light * new_l->colour.g_colour;
		intens.b_colour += light * new_l->colour.b_colour;
		sp.ind_l_n++;
		new_l = new_l->next;
	}
	intens.r_colour += scene->ambi.racio * scene->ambi.colour.r_colour;
	intens.g_colour += scene->ambi.racio * scene->ambi.colour.g_colour;
	intens.b_colour += scene->ambi.racio * scene->ambi.colour.b_colour;
	return (intens);
}

t_colour	find_colour_2(t_scene *scene, int x, int y, t_index fig)
{
	double		light;
	t_light		*new_l;
	t_colour	intens;
	
	new_l = scene->light;
	intens = init_colour();
	while (new_l)
	{
		light = check_light_2(scene, x, y, fig);
		intens.r_colour += light * new_l->colour.r_colour;
		intens.g_colour += light * new_l->colour.g_colour;
		intens.b_colour += light * new_l->colour.b_colour;
		fig.ind_l_n++;
		new_l = new_l->next;
	}
	intens.r_colour += scene->ambi.racio * scene->ambi.colour.r_colour;
	intens.g_colour += scene->ambi.racio * scene->ambi.colour.g_colour;
	intens.b_colour += scene->ambi.racio * scene->ambi.colour.b_colour;
	return (intens);
}