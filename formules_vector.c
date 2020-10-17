/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formules_vector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:07:44 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/16 22:09:51 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft/libft.h"
#include "get_next_line.h"
#include "minilibx_mms/mlx.h"

t_xyzpoint	vector_mult(t_xyzpoint vector_1, t_xyzpoint vector_2)
{
	t_xyzpoint	v_mult;

	v_mult.x = vector_1.z * vector_2.y - vector_1.y * vector_2.z;
	v_mult.y = vector_1.x * vector_2.z - vector_1.z * vector_2.x;
	v_mult.z = vector_1.y * vector_2.x - vector_1.x * vector_2.y;
	return (v_mult);
}

double		length_vector(t_xyzpoint vector)
{
	return (sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2)));
}

t_xyzpoint	substruct_vector(t_xyzpoint vect_1, t_xyzpoint vect_2)
{
	t_xyzpoint	result;

	result.x = vect_1.x - vect_2.x;
	result.y = vect_1.y - vect_2.y;
	result.z = vect_1.z - vect_2.z;
	return (result);
}

t_xyzpoint	normalize_vector(t_xyzpoint vect)
{
	t_xyzpoint	norm_vect;

	norm_vect.x = vect.x / length_vector(vect);
	norm_vect.y = vect.y / length_vector(vect);
	norm_vect.z = vect.z / length_vector(vect);
	return (norm_vect);
}

double		scalar(t_xyzpoint vector_1, t_xyzpoint vector_2)
{
	return (vector_1.x * vector_2.x + vector_1.y * vector_2.y + \
		vector_1.z * vector_2.z);
}
