/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 07:57:48 by jceia             #+#    #+#             */
/*   Updated: 2021/10/13 10:22:52 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "matrix.h"

t_matrix	*matrix3x3_rotation_x(float theta)
{
	t_matrix	*m;

	m = matrix_zeros(3, 3);
	if (!m)
		return (NULL);
	m->data[0] = 1.0;
	m->data[4] = cos(theta);
	m->data[5] = -sin(theta);
	m->data[7] = sin(theta);
	m->data[8] = cos(theta);
	return (m);
}

t_matrix	*matrix3x3_rotation_y(float theta)
{
	t_matrix	*m;

	m = matrix_zeros(3, 3);
	if (!m)
		return (NULL);
	m->data[0] = cos(theta);
	m->data[2] = sin(theta);
	m->data[4] = 1.0;
	m->data[6] = -sin(theta);
	m->data[8] = cos(theta);
	return (m);
}

t_matrix	*matrix3x3_rotation_z(float theta)
{
	t_matrix	*m;

	m = matrix_zeros(3, 3);
	if (!m)
		return (NULL);
	m->data[0] = cos(theta);
	m->data[1] = -sin(theta);
	m->data[3] = sin(theta);
	m->data[4] = cos(theta);
	m->data[8] = 1.0;
	return (m);
}

t_matrix	*matrix3x3_rotation_xyz(const t_vec3d *angles)
{
	t_matrix	*m;

	m = matrix3x3_rotation_z(angles->z);
	m = matrix_mul(matrix3x3_rotation_y(angles->y), m, true);
	m = matrix_mul(matrix3x3_rotation_x(angles->x), m, true);
	return (m);
}
