/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 12:35:16 by jceia             #+#    #+#             */
/*   Updated: 2021/10/14 12:06:28 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray3d	ray3d_create(t_vec3d origin, t_vec3d direction)
{
	t_ray3d	r;

	r.origin = origin;
	r.direction = vec3d_normalize(direction);
	return (r);
}

t_ray3d	ray3d_from_two_points(t_vec3d p, t_vec3d q)
{
	t_ray3d	r;

	r.origin = p;
	r.direction = vec3d_normalize(vec3d_subtract(q, p));
	return (r);
}

t_vec3d	ray3d_at(const t_ray3d *ray, float t)
{
	return (vec3d_add(ray->origin, vec3d_scalar_mul(ray->direction, t)));
}

t_ray3d	ray3d_reflected(const t_ray3d *ray, t_vec3d normal)
{
	t_vec3d	v;
	float	a;

	a = vec3d_dot_product(ray->direction, normal);
	v = vec3d_subtract(ray->direction, vec3d_scalar_mul(normal, 2 * a));
	return (ray3d_create(ray->origin, v));
}
