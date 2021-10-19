/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 07:47:21 by jceia             #+#    #+#             */
/*   Updated: 2021/10/16 22:26:18 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <vec.h>
#include <math.h>
#include <stdio.h>

void	camera_set_basis(t_matrix **basis, t_vec3d direction)
{
	t_vec3d	v;
	t_vec3d	up_vec;

	*basis = matrix_empty(3, 3);
	(*basis)->data[2] = direction.x;
	(*basis)->data[5] = direction.y;
	(*basis)->data[8] = direction.z;
	if (direction.y == 1.0)
		up_vec = vec3d_create(0.0, 0.0, 1.0);
	else
		up_vec = vec3d_create(0.0, -1.0, 0.0);
	v = vec3d_cross_product(direction, up_vec);
	(*basis)->data[0] = v.x;
	(*basis)->data[3] = v.y;
	(*basis)->data[6] = v.z;
	v = vec3d_cross_product(direction, v);
	(*basis)->data[1] = v.x;
	(*basis)->data[4] = v.y;
	(*basis)->data[7] = v.z;
}

void	calculate_camera_params(t_camera *cam, int win_width, int win_height)
{
	cam->direction = vec3d_normalize(cam->direction);
	camera_set_basis(&cam->basis, cam->direction);
	cam->pixels_width = win_width;
	cam->pixels_height = win_height;
	cam->view_width = 2 * tan(M_PI * cam->fov / 360);
	cam->view_height = win_height * cam->view_width / win_width;
	cam->proj_type = PROJ;
}

void	camera_clean(void *ptr)
{
	t_camera	*cam;

	if (ptr)
	{
		cam = (t_camera *)ptr;
		if (cam->basis)
			matrix_clear(cam->basis);
		free(cam);
	}
}