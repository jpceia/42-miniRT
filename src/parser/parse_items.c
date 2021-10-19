/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_items.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 12:29:55 by jceia             #+#    #+#             */
/*   Updated: 2021/10/16 22:22:33 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>  // O_RDONLY
#include "libft.h"
#include "miniRT.h"
#include <stdio.h>

t_data	*parse_ambient_from_line(t_data *vars, char *line)
{
	int		n;
	char	**s_split;

	n = ft_strwc(line, ' ');
	if (n != 3)
		return (clean_exit(NULL, "Line with incorrect format", NULL, 0));
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (clean_exit(NULL, "Error spliting line", NULL, 0));
	vars->ambient.ratio = ft_atof(s_split[1]);
	if (!parse_color(&vars->ambient.color, s_split[2]))
		return (clean_exit(NULL, "Error parsing rgb color", NULL, 0));
	ft_str_array_clear(s_split, n);
	return (vars);
}

t_data	*parse_camera_from_line(t_data *vars, char *line)
{
	char		**s_split;
	int			n;

	n = ft_strwc(line, ' ');
	if (n != 4)
		return (clean_exit(NULL, "Line with incorrect format", NULL, 0));
	vars->camera = (t_camera *)malloc(sizeof(*vars->camera));
	if (!vars->camera)
		return (clean_exit(NULL, "Error allocating memory", NULL, 0));
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (clean_exit(vars->camera, "Error spliting line", free, 0));
	if (!parse_vec3d(&vars->camera->origin, s_split[1]))
		return (clean_exit(vars->camera, "Error parsing vector", free, 0));
	if (!parse_vec3d(&vars->camera->direction, s_split[2]))
		return (clean_exit(vars->camera, "Error parsing vector", free, 0));
	vars->camera->fov = ft_atof(s_split[3]);
	ft_str_array_clear(s_split, n);
	return (vars);
}

t_data	*parse_light_from_line(t_data *vars, char *line)
{
	t_light	*light;
	char	**s_split;
	int		n;

	n = ft_strwc(line, ' ');
	if (n < 3 || n > 4)
		return (clean_exit(NULL, "Line with incorrect format", NULL, 0));
	light = (t_light *)malloc(sizeof(*light));
	if (!light)
		return (clean_exit(NULL, "Error allocating memory", NULL, 0));
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (clean_exit(light, "Error spliting line", free, 0));
	if (!parse_vec3d(&light->origin, s_split[1]))
		return (clean_exit(light, "Error parsing vector", free, 0));
	light->ratio = ft_atof(s_split[2]);
	light->color = vec3d_create(1.0, 1.0, 1.0);
	if (n == 4)
		if (!parse_color(&light->color, s_split[3]))
			return (clean_exit(light, "Error parsing rgb color", free, 0));
	ft_str_array_clear(s_split, n);
	ft_lstpush_front(&vars->lights, light);
	return (vars);
}
