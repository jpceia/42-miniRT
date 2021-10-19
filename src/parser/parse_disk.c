/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_disk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 09:27:20 by jceia             #+#    #+#             */
/*   Updated: 2021/10/14 09:30:12 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_object	*parse_disk_from_line(t_object *obj, char *line)
{
	t_disk	*disk;
	char    **s_split;
	int		n;

	obj->obj_type = DISK;
	n = ft_strwc(line, ' ');
	if (n != 5)
		return (clean_exit(NULL, "Line with incorrect format", NULL, 0));
	disk = (t_disk *)malloc(sizeof(*disk));
	if (!disk)
		return (clean_exit(NULL, "Error allocating memory", NULL, 0));
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (clean_exit(disk, "Error spliting line", free, 0));
    if (!parse_vec3d(&disk->center, s_split[1]))
		return (clean_exit(disk, "Error parsing vector", free, 0));
	if (!parse_vec3d(&disk->n, s_split[2]))
		return (clean_exit(disk, "Error parsing vector", free, 0));
	disk->radius = ft_atof(s_split[3]);
	if (!parse_color(&disk->color, s_split[4]))
		return (clean_exit(disk, "Error parsing rgb color", free, 0));
	ft_str_array_clear(s_split, n);
	obj->data = disk;
	return (obj);
}
