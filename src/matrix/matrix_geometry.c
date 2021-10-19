/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_geometry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 07:16:53 by jceia             #+#    #+#             */
/*   Updated: 2021/10/13 12:54:52 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "matrix.h"

t_matrix	*matrix_scaling3d(const t_vec3d *s)
{
	t_matrix	*m;

	m = matrix_zeros(3, 3);
	if (!m)
		return (NULL);
	m->data[0] = s->x;
	m->data[4] = s->y;
	m->data[8] = s->z;
	return (m);
}

t_vec3d	matrix_mul_vec3d(t_matrix *m, const t_vec3d *p)
{
	t_vec3d	q;

	if (!m)
		return (vec3d_origin());
	if (!check_matrix_ncols(m->ncols, 3) || !check_matrix_nrows(m->nrows, 3))
		return (vec3d_origin());
	q.x = m->data[0] * p->x + m->data[1] * p->y + m->data[2] * p->z;
	q.y = m->data[3] * p->x + m->data[4] * p->y + m->data[5] * p->z;
	q.z = m->data[6] * p->x + m->data[7] * p->y + m->data[8] * p->z;
	return (q);
}
