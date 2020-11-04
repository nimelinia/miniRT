/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formules_vector_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:50:24 by scopycat          #+#    #+#             */
/*   Updated: 2020/10/30 15:05:26 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minilibx_mms/mlx.h"

t_xyzpoint		mult_num_vect(t_xyzpoint vector, double num)
{
	t_xyzpoint	result;

	result.x = vector.x * num;
	result.y = vector.y * num;
	result.z = vector.z * num;
	return (result);
}

t_xyzpoint		vector_div(t_xyzpoint vect, double num)
{
	t_xyzpoint	res;

	res.x = vect.x / num;
	res.y = vect.y / num;
	res.z = vect.z / num;
	return (res);
}

t_xyzpoint		sum_vect(t_xyzpoint vect_1, t_xyzpoint vect_2)
{
	t_xyzpoint	sum;

	sum.x = vect_1.x + vect_2.x;
	sum.y = vect_1.y + vect_2.y;
	sum.z = vect_1.z + vect_2.z;
	return (sum);
}
