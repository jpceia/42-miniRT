/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:02:28 by jceia             #+#    #+#             */
/*   Updated: 2021/10/19 02:25:13 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

t_rgb	hit_light_contribution(const t_ray3d *reflected_ray,
		const t_hit_record *hit_record, const t_light *light,
		const t_data *vars)
{
	t_hit_record	hit_before_light;
	t_ray3d			ray_to_light;
	float			diffuse_intensity;

	(void)reflected_ray;
	ray_to_light = ray3d_from_two_points(hit_record->p, light->origin);
	if (raytrace_hit(&ray_to_light, vars, 1e-3, &hit_before_light))
		if (hit_before_light.t < vec3d_norm(
				vec3d_subtract(light->origin, hit_record->p)))
			return (vec3d_origin());
	diffuse_intensity = vec3d_dot_product(
			ray_to_light.direction, hit_record->n) * light->ratio;
	if (diffuse_intensity < 0)
		diffuse_intensity = 0;
	return (vec3d_scalar_mul(light->color, diffuse_intensity));
}

t_rgb	hit_color(const t_ray3d *reflected_ray,
		const t_hit_record *hit_record, const t_data *vars)
{
	t_vec3d			color_shadow;
	t_list			*lights;

	lights = vars->lights;
	color_shadow = vec3d_scalar_mul(
			vars->ambient.color, vars->ambient.ratio);
	while (lights)
	{
		color_shadow = vec3d_add(color_shadow,
				hit_light_contribution(reflected_ray,
					hit_record, lights->content, vars));
		lights = lights->next;
	}
	return (vec3d_elementwise_product(hit_record->base_color, color_shadow));
}
