/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2D_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 06:48:02 by jceia             #+#    #+#             */
/*   Updated: 2021/10/13 14:18:46 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "vec.h"

t_vec2d	vec2d_scalar_mul(t_vec2d v, float l)
{
	v.x *= l;
	v.y *= l;
	return (v);
}

t_vec2d	vec2d_normalize(t_vec2d v)
{
	return (vec2d_scalar_mul(v, 1 / vec2d_norm(v)));
}

float	vec2d_dot_product(t_vec2d u, t_vec2d v)
{
	return (u.x * v.x + u.y * v.y);
}

float	vec2d_cross_product(t_vec2d u, t_vec2d v)
{
	return (u.x * u.y - u.y * v.x);
}

t_vec2d	vec2d_interpolate(t_vec2d p, t_vec2d q, float t)
{
	t_vec2d	r;

	r.x = t * q.x + (1 - t) * p.x;
	r.y = t * q.y + (1 - t) * p.y;
	return (r);
}
