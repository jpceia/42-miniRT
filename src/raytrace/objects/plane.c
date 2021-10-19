/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 06:42:25 by jceia             #+#    #+#             */
/*   Updated: 2021/10/13 20:24:38 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Checks if a ray hits a plane
 * Plane equation: < p - p0 , n > = 0
 * Ray equation: r(t) = r0 + t * d, t > 0
 * 
 * Merging the two we get the following equation
 *   <t * d + r0 - p0, n > = 0
 * Equiv. to:
 *   t = - <v,n> / <d,n>
 * with v = r0 - p0
 */
t_bool	hit_plane(const t_ray3d *ray, const t_plane *plane,
		float t_min, t_hit_record *record)
{
	t_vec3d	v;
	float	dot_prod;

	record->base_color = plane->color;
	record->n = plane->n;
	dot_prod = vec3d_dot_product(plane->n, ray->direction);
	if (dot_prod == 0)
		return (false);
	v = vec3d_subtract(ray->origin, plane->p);
	record->t = -vec3d_dot_product(v, plane->n) / dot_prod;
	if (record->t < t_min)
		return (false);
	record->p = ray3d_at(ray, record->t);
	return (true);
}
