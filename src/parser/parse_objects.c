/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 12:26:46 by jceia             #+#    #+#             */
/*   Updated: 2021/10/19 01:44:38 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "miniRT.h"

t_data	*parse_object_from_line(t_data *vars, char *line)
{
	t_object	*obj;

	obj = (t_object *)malloc(sizeof(*obj));
	if (!obj)
		return (clean_exit(NULL, "Error allocating memory", NULL, 0));
	if (strncmp(line, "sp ", 3) == 0)
	{
		if (!parse_sphere_from_line(obj, line))
			return (clean_exit(obj, "Unable to parse sphere object", free, 0));
	}
	else if (strncmp(line, "pl ", 3) == 0)
	{
		if (!parse_plane_from_line(obj, line))
			return (clean_exit(obj, "Unable to parse plane object", free, 0));
	}
	else if (strncmp(line, "cy ", 3) == 0)
	{
		if (!parse_cylinder_from_line(obj, line))
			return (clean_exit(obj, "Unable to parse cylinder obj", free, 0));
	}
	else if (strncmp(line, "tr ", 3) == 0)
	{
		if (!parse_triangle_from_line(obj, line))
			return (clean_exit(obj, "Unable to parse triangle obj", free, 0));
	}
	else if (strncmp(line, "di ", 3) == 0)
	{
		if (!parse_disk_from_line(obj, line))
			return (clean_exit(obj, "Unable to parse disk obj", free, 0));
	}
	else
		return (clean_exit(obj, "Unrecognized object type", free, 0));
	ft_lstpush_front(&vars->objects, obj);
	return (vars);
}

t_object	*parse_sphere_from_line(t_object *obj, char *line)
{
	t_sphere	*sphere;
	char		**s_split;
	int			n;

	obj->obj_type = SPHERE;
	n = ft_strwc(line, ' ');
	if (n != 4)
		return (clean_exit(NULL, "Line with incorrect format", NULL, 0));
	sphere = (t_sphere *)malloc(sizeof(*sphere));
	if (!sphere)
		return (clean_exit(NULL, "Error allocating memory", NULL, 0));
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (clean_exit(sphere, "Error spliting line", free, 0));
	if (!parse_vec3d(&sphere->center, s_split[1]))
		return (clean_exit(sphere, "Error parsing vector", free, 0));
	sphere->radius = ft_atof(s_split[2]) / 2;
	if (!parse_color(&sphere->color, s_split[3]))
		return (clean_exit(sphere, "Error parsing rgb color", free, 0));
	ft_str_array_clear(s_split, n);
	obj->data = sphere;
	return (obj);
}

t_object	*parse_plane_from_line(t_object *obj, char *line)
{
	t_plane	*plane;
	char	**s_split;
	int		n;

	obj->obj_type = PLANE;
	n = ft_strwc(line, ' ');
	if (n != 4)
		return (clean_exit(NULL, "Line with incorrect format", NULL, 0));
	plane = (t_plane *)malloc(sizeof(*plane));
	if (!plane)
		return (clean_exit(NULL, "Error allocating memory", NULL, 0));
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (clean_exit(plane, "Error spliting line", free, 0));
	if (!parse_vec3d(&plane->p, s_split[1]))
		return (clean_exit(plane, "Error parsing vector", free, 0));
	if (!parse_vec3d(&plane->n, s_split[2]))
		return (clean_exit(plane, "Error parsing vector", free, 0));
	if (!parse_color(&plane->color, s_split[3]))
		return (clean_exit(plane, "Error parsing rgb color", free, 0));
	plane->n = vec3d_normalize(plane->n);
	ft_str_array_clear(s_split, n);
	obj->data = plane;
	return (obj);
}

t_object	*parse_cylinder_from_line(t_object *obj, char *line)
{
	t_cylinder	*cylinder;
	char		**s_split;
	int			n;

	obj->obj_type = CYLINDER;
	n = ft_strwc(line, ' ');
	if (n != 6)
		return (clean_exit(NULL, "Line with incorrect format", NULL, 0));
	cylinder = (t_cylinder *)malloc(sizeof(*cylinder));
	if (!cylinder)
		return (clean_exit(NULL, "Error allocating memory", NULL, 0));
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (clean_exit(cylinder, "Error spliting line", free, 0));
	if (!parse_vec3d(&cylinder->p, s_split[1]))
		return (clean_exit(cylinder, "Error parsing vector", free, 0));
	if (!parse_vec3d(&cylinder->direction, s_split[2]))
		return (clean_exit(cylinder, "Error parsing vector", free, 0));
	cylinder->direction = vec3d_normalize(cylinder->direction);
	cylinder->radius = ft_atof(s_split[3]) / 2;
	cylinder->height = ft_atof(s_split[4]);
	if (!parse_color(&cylinder->color, s_split[5]))
		return (clean_exit(cylinder, "Error parsing rgb color", free, 0));
	ft_str_array_clear(s_split, n);
	obj->data = cylinder;
	return (obj);
}
