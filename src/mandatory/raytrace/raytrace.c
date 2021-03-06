/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:00:21 by jceia             #+#    #+#             */
/*   Updated: 2021/10/21 22:30:03 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	convert_scale(int i, float view_size, float screen_size)
{
	return (view_size * ((i + 0.5) / screen_size - 0.5));
}

void	raytrace_scenario(t_data *vars)
{
	t_camera	*cam;
	t_ray3d		ray;
	t_vec3d		v;
	int			i;
	int			j;

	cam = vars->camera;
	i = 0;
	while (i < cam->pixels_height)
	{
		j = 0;
		while (j < cam->pixels_width)
		{
			v = vec3d_create(
					convert_scale(j, cam->view_width, cam->pixels_width),
					-convert_scale(i, cam->view_height, cam->pixels_height),
					1);
			ray = ray3d_create(cam->origin, matrix_mul_vec3d(cam->basis, &v));
			vars->buf[i * cam->pixels_width + j] = raytrace_single(&ray, vars);
			j++;
		}
		i++;
	}
}

t_bool	raytrace_hit(const t_ray3d *ray, const t_data *vars,
		float t_min, t_hit_record *record)
{
	t_bool			hit_anything;
	t_hit_record	hit_rec;
	t_list			*objs;

	objs = vars->objects;
	hit_anything = false;
	while (objs)
	{
		if (hit_object(ray, objs->content, t_min, &hit_rec))
		{
			if (!hit_anything || record->t > hit_rec.t)
				ft_memcpy(record, &hit_rec, sizeof(t_hit_record));
			hit_anything = true;
		}
		objs = objs->next;
	}
	if (hit_anything)
	{
		if (vec3d_dot_product(ray->direction, record->normal) > 0)
			record->normal = vec3d_scalar_mul(record->normal, -1);
		record->reflected = ray3d_reflected(ray, record->normal).direction;
	}
	return (hit_anything);
}

t_rgb	raytrace_single(const t_ray3d *primary_ray, const t_data *vars)
{
	t_hit_record	hit_record;

	if (raytrace_hit(primary_ray, vars, 0, &hit_record))
		return (hit_color(&hit_record, vars));
	return (vars->ambient.color);
}
