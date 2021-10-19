/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:00:21 by jceia             #+#    #+#             */
/*   Updated: 2021/10/16 22:29:01 by jceia            ###   ########.fr       */
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
		if (vec3d_dot_product(ray->direction, record->n) > 0)
			record->n = vec3d_scalar_mul(record->n, -1);
	}
	return (hit_anything);
}

t_rgb	raytrace_single(const t_ray3d *primary_ray, const t_data *vars)
{
	t_hit_record	hit_record;

	if (raytrace_hit(primary_ray, vars, 0, &hit_record))
		return (hit_color(NULL, &hit_record, vars));
	return (vars->ambient.color);
}


t_bool	hit_object(const t_ray3d *ray, t_object *obj,
		float t_min, t_hit_record *record)
{
	record->obj = obj;
	if (obj->obj_type == SPHERE)
		return (hit_sphere(ray, obj->data, t_min, record));
	if (obj->obj_type == PLANE)
		return (hit_plane(ray, obj->data, t_min, record));
	if (obj->obj_type == CYLINDER)
		return (hit_cylinder(ray, obj->data, t_min, record));
	if (obj->obj_type == TRIANGLE)
		return (hit_triangle(ray, obj->data, t_min, record));
	if (obj->obj_type == DISK)
		return (hit_disk(ray, obj->data, t_min, record));
	return (false);
}
