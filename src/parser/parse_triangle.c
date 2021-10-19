/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:08:52 by jceia             #+#    #+#             */
/*   Updated: 2021/10/14 09:13:51 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_object	*parse_triangle_from_line(t_object *obj, char *line)
{
	t_triangle	*triangle;
	char    **s_split;
	int		n;

	obj->obj_type = TRIANGLE;
	n = ft_strwc(line, ' ');
	if (n != 5)
		return (clean_exit(NULL, "Line with incorrect format", NULL, 0));
	triangle = (t_triangle *)malloc(sizeof(*triangle));
	if (!triangle)
		return (clean_exit(NULL, "Error allocating memory", NULL, 0));
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (clean_exit(triangle, "Error spliting line", free, 0));
	if (!parse_vec3d(&triangle->p1, s_split[1]))
		return (clean_exit(triangle, "Error parsing vector", free, 0));
	if (!parse_vec3d(&triangle->p2, s_split[2]))
		return (clean_exit(triangle, "Error parsing vector", free, 0));
	if (!parse_vec3d(&triangle->p3, s_split[3]))
		return (clean_exit(triangle, "Error parsing vector", free, 0));
	if (!parse_color(&triangle->color, s_split[4]))
		return (clean_exit(triangle, "Error parsing rgb color", free, 0));
	ft_str_array_clear(s_split, n);
	obj->data = triangle;
	return (obj);
}
