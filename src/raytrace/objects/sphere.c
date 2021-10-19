/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 06:43:03 by jceia             #+#    #+#             */
/*   Updated: 2021/10/14 21:18:44 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

/*
 * Checks if a ray hits a sphere
 * Sphere equation: || p - p0 || = R
 * Ray equation: r(t) = r0 + t * d, t > 0
 * 
 * Hence we have a 2nd degree equation
 * <d,d> t^2 + 2 <r0 - p0, d> t + <r0 - p0, r0 - p0> - R^2 = 0
 * 
 * In this case
 * a = <d,d> = 1 (direction in ray is an unit vector)
 * v = r0 - p0
 * h = <v, d>
 * t = (-b +- sqrt(b*b-4*a*c) / (2 * a)) = -h +- sqrt(disc)
 * disc = h * h - c
 */
t_bool	hit_sphere(const t_ray3d *ray, const t_sphere *sphere,
		float t_min, t_hit_record *record)
{
	float	half_b;
	float	discriminant;
	float	sqrt_disc;
	t_vec3d	v;
	
	record->base_color = sphere->color;
	v = vec3d_subtract(ray->origin, sphere->center);
	half_b = vec3d_dot_product(v, ray->direction);
	discriminant = half_b * half_b;
	discriminant -= vec3d_norm_squared(v) - sphere->radius * sphere->radius;
	if (discriminant < 0)
		return (false);
	sqrt_disc = sqrtf(discriminant);
	if (-half_b + sqrt_disc < t_min)
		return (false);
	if (-half_b - sqrt_disc < t_min)
		record->t = -half_b + sqrt_disc;
	else
		record->t = -half_b - sqrt_disc;
	record->p = ray3d_at(ray, record->t);
	record->n = vec3d_normalize(vec3d_subtract(record->p, sphere->center));
	return (true);
}
