/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3D_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 06:48:02 by jceia             #+#    #+#             */
/*   Updated: 2021/10/13 14:18:31 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "vec.h"

t_vec3d	vec3d_scalar_mul(t_vec3d v, float l)
{
	v.x *= l;
	v.y *= l;
	v.z *= l;
	return (v);
}

t_vec3d	vec3d_normalize(t_vec3d v)
{
	return (vec3d_scalar_mul(v, 1 / vec3d_norm(v)));
}

float	vec3d_dot_product(t_vec3d u, t_vec3d v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec3d	vec3d_cross_product(t_vec3d u, t_vec3d v)
{
	t_vec3d	w;

	w.x = u.y * v.z - u.z * v.y;
	w.y = u.z * v.x - u.x * v.z;
	w.z = u.x * v.y - u.y * v.x;
	return (w);
}

t_vec3d	vec3d_interpolate(t_vec3d p, t_vec3d q, float t)
{
	t_vec3d	r;

	r.x = t * q.x + (1 - t) * p.x;
	r.y = t * q.y + (1 - t) * p.y;
	r.z = t * q.z + (1 - t) * p.z;
	return (r);
}
