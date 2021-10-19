/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:47:48 by jceia             #+#    #+#             */
/*   Updated: 2021/10/16 22:20:56 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include "miniRT.h"

void	object_clean(void *obj)
{
	if (!obj)
		return ;
	free(((t_object *)obj)->data);
	free(obj);
}

void	mlx_data_clean(void *ptr)
{
	t_data	*vars;

	if (!ptr)
		return ;
	vars = (t_data *)ptr;
	if (vars->win)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		vars->win = NULL;
	}
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		vars->mlx = NULL;
	}
	camera_clean(vars->camera);
	ft_lstclear(&vars->lights, free);
	ft_lstclear(&vars->objects, object_clean);
	if (vars->buf)
	{
		free(vars->buf);
		vars->buf = NULL;
	}
	free(vars);
}

void	*clean_exit(void *ptr, char *msg, void (*del)(void *), int do_exit)
{
	perror(msg);
	if (del)
		del(ptr);
	if (do_exit)
		exit(EXIT_FAILURE);
	return (NULL);
}
