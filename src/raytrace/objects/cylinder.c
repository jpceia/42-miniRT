/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 06:42:00 by jceia             #+#    #+#             */
/*   Updated: 2021/10/19 10:23:59 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

float	hit_cylinder_dist(const t_ray3d *ray, const t_cylinder *cylinder,
		float min_dist, t_float_pair *t_pair)
{
	float	t;
	float	v_dot_n;
	float	d_dot_n;
	float	h;
	t_vec3d	v;

	t = t_pair->max;
	if (t < min_dist)
		return (-1);
	v = vec3d_subtract(ray->origin, cylinder->p);
	v_dot_n = vec3d_dot_product(v, cylinder->direction);
	d_dot_n = vec3d_dot_product(ray->direction, cylinder->direction);
	if (t_pair->min >= min_dist)
	{
		h = v_dot_n + t_pair->min * d_dot_n;
		if (h >= 0 && h <= cylinder->height)
			t = t_pair->min;
	}
	if (t != t_pair->min)
	{
		h = v_dot_n + t * d_dot_n;
		if (h < 0 || h > cylinder->height)
			return (-1);
	}
	return (t);
}

void	hit_cylinder_fill_record(const t_ray3d *ray, const t_cylinder *cylinder,
		t_hit_record *record)
{
	record->base_color = cylinder->color;
	record->p = ray3d_at(ray, record->t);
	record->n = vec3d_subtract(record->p, cylinder->p);
	record->n = vec3d_subtract(record->n, vec3d_scalar_mul(cylinder->direction,
				vec3d_dot_product(record->n, cylinder->direction)));
	record->n = vec3d_normalize(record->n);
}

/*
 * Checks if a ray hits a cylinder
 * The equation of a cylinder is:
 * 	|(p - p0) x n)| = R
 * 	<p - p0, n> \in [0, height]
 * Substituting p by our ray r(t) = r0 + t * d, t > 0
 * We have a 2nd degree equation
 * R^2 = |(r0 - p0 + t * d) x n|^2 = |(r0 - p0) x n + (d x n) * t|^2
 *     = |d x n|^2 t^2 + 2 * t * <d x n, v x n> + |v x n|^2 
 * with v = r0 - p0
 * 
 * the coeficients of "a * t^2 + b * t + c = 0" are
 * a = |d x n|^2
 * b = 2 * <d x n, v x n>
 * c = |v x n|^2 - R^2
 * 
 * The solution is t = -h +- sqrt(h^2 - c)
 * with h = b / (2 * a)
 * 
 * Regarding the height of the cylinder, we still have
 * <r(t) - p0, n> = <d * t + v, n> = t * <d,n> + <v, n> between 0 and H
 * with v = r0 - p0
 */
t_bool	hit_cylinder(const t_ray3d *ray, const t_cylinder *cylinder,
		float t_min, t_hit_record *record)
{
	t_float_pair	t_pair;
	t_vec3d			v;
	t_vec3d			d_cross_n;
	t_vec3d			v_cross_n;
	t_deg2_eq_coefs	params;

	v = vec3d_subtract(ray->origin, cylinder->p);
	d_cross_n = vec3d_cross_product(ray->direction, cylinder->direction);
	v_cross_n = vec3d_cross_product(v, cylinder->direction);
	params.a = vec3d_norm_squared(d_cross_n);
	params.b = 2 * vec3d_dot_product(d_cross_n, v_cross_n);
	params.c = vec3d_norm_squared(v_cross_n);
	params.c -= cylinder->radius * cylinder->radius;
	if (!deg2_eq_solutions(&params, &t_pair))
		return (false);
	record->t = hit_cylinder_dist(ray, cylinder, t_min, &t_pair);
	if (record->t < 0)
		return (false);
	hit_cylinder_fill_record(ray, cylinder, record);
	return (true);
}
