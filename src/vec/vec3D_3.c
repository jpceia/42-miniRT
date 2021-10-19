/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3D_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 09:39:38 by jceia             #+#    #+#             */
/*   Updated: 2021/10/13 10:20:41 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "libft.h"
#include "vec.h"

float	vec3d_norm_squared(t_vec3d v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

float	vec3d_norm(t_vec3d v)
{
	return (sqrtf(vec3d_norm_squared(v)));
}

float	vec3d_angle(t_vec3d u, t_vec3d v)
{
	float	norm_u;
	float	norm_v;
	float	dot_uv;

	dot_uv = vec3d_dot_product(u, v);
	norm_u = vec3d_norm(u);
	norm_v = vec3d_norm(v);
	if (norm_u == 0 || norm_v == 0)
	{
		ft_putstr_error("Vector with zero length\n");
		return (0);
	}
	return (dot_uv / norm_u / norm_v);
}

t_vec3d	vec3d_elementwise_product(t_vec3d u, t_vec3d v)
{
	u.x *= v.x;
	u.y *= v.y;
	u.z *= v.z;
	return (u);
}

t_vec3d	vec3d_clip(t_vec3d v, float a, float b)
{
	v.x = fminf(fmaxf(v.x, a), b);
	v.y = fminf(fmaxf(v.y, a), b);
	v.z = fminf(fmaxf(v.z, a), b);
	return (v);
}
