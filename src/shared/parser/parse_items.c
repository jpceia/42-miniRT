/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_items.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 12:29:55 by jceia             #+#    #+#             */
/*   Updated: 2021/10/25 18:03:13 by jceia            ###   ########.fr       */
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
		return (clean_exit(NULL, LINE_FMT_ERR, NULL, 0));
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (clean_exit(NULL, SPLIT_ERR, NULL, 0));
	vars->ambient.ratio = ft_atof(s_split[1]);
	if (!parse_rgb(&vars->ambient.color, s_split[2]))
		return (clean_exit(NULL, PARSE_RGB_ERR, NULL, 0));
	ft_str_array_clear(s_split, n);
	return (vars);
}

t_data	*parse_camera_from_line(t_data *vars, char *line)
{
	t_camera	*cam;
	char		**s_split;
	int			n;

	n = ft_strwc(line, ' ');
	if (n != 4)
		return (clean_exit(NULL, LINE_FMT_ERR, NULL, 0));
	cam = (t_camera *)malloc(sizeof(*cam));
	if (!cam)
		return (clean_exit(NULL, MALLOC_ERR, NULL, 0));
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (clean_exit(cam, SPLIT_ERR, free, 0));
	if (!parse_vec3d(&cam->origin, s_split[1]))
		return (clean_exit(cam, PARSE_VEC_ERR, free, 0));
	if (!parse_vec3d(&cam->direction, s_split[2]))
		return (clean_exit(cam, PARSE_VEC_ERR, free, 0));
	cam->fov = ft_atof(s_split[3]);
	vars->camera = cam;
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
		return (clean_exit(NULL, LINE_FMT_ERR, NULL, 0));
	light = (t_light *)malloc(sizeof(*light));
	if (!light)
		return (clean_exit(NULL, MALLOC_ERR, NULL, 0));
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (clean_exit(light, SPLIT_ERR, free, 0));
	if (!parse_vec3d(&light->origin, s_split[1]))
		return (clean_exit(light, PARSE_VEC_ERR, free, 0));
	light->ratio = ft_atof(s_split[2]);
	light->color = vec3d_create(1.0, 1.0, 1.0);
	if (n == 4)
		if (!parse_rgb(&light->color, s_split[3]))
			return (clean_exit(light, PARSE_RGB_ERR, free, 0));
	ft_str_array_clear(s_split, n);
	ft_lstpush_front(&vars->lights, light);
	return (vars);
}
