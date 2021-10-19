/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 21:36:12 by jceia             #+#    #+#             */
/*   Updated: 2021/10/14 22:12:03 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_bool	hit_triangle(const t_ray3d *ray, const t_triangle *triangle,
		float t_min, t_hit_record *record)
{
    t_vec3d u;
	t_vec3d	v;
    t_vec3d w;
	float   a;
    float   b;
    float	dot_prod;

    record->base_color = triangle->color;
    u = vec3d_subtract(triangle->p2, triangle->p1);
    v = vec3d_subtract(triangle->p3, triangle->p1);
    record->n = vec3d_normalize(vec3d_cross_product(v, u));
	dot_prod = vec3d_dot_product(record->n, ray->direction);
	if (dot_prod == 0)
		return (false);
	w = vec3d_subtract(ray->origin, triangle->p1);
	record->t = -vec3d_dot_product(w, record->n) / dot_prod;
	if (record->t < t_min)
		return (false);
	record->p = ray3d_at(ray, record->t);
    a = vec3d_dot_product(record->p, u) / vec3d_norm_squared(u);
    b = vec3d_dot_product(record->p, v) / vec3d_norm_squared(v);
    if (a >= 0 && b >= 0 && a + b <= 1)
	    return (true);
    return (false);
}
