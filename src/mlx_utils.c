/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   mlx_utils.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jceia <jceia@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2021/09/01 20:28:58 by jceia			 #+#	#+#			 */
/*   Updated: 2021/09/02 00:22:11 by jceia			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include <mlx.h>
#include "miniRT.h"
#include "libft.h"

/*
 * TODO
 * add_shape
 * is a function that accepts a double (distance) and a int (color) as
 * arguments, 0 will add no shading to the color, whilst 1 will make the
 * color completely dark. 0.5 will dim it halfway, and .25 a quarter way.
 * You get the point.
 */
void	plot_pixel(t_data *vars, float x, float y, t_rgb color)
{
	int		i;
	int		j;
	char	*dst;

	i = (int)(x + 0.5);
	j = (int)(y + 0.5);
	if (i < 0 || i >= vars->width || j < 0 || j >= vars->height)
		return ;
	dst = vars->addr + (j * vars->line_length + i * (vars->bits_per_pixel / 8));
	*(unsigned int *)dst += create_trgb(color);
}

void	update_image_from_buf(t_data *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->height)
	{
		j = 0;
		while (j < vars->width)
		{
			plot_pixel(vars, j, i, vars->buf[i * vars->width + j]);
			j++;
		}
		i++;
	}
}

void	mlx_data_update_image(t_data *vars)
{
	calculate_camera_params(
		vars->camera, vars->width, vars->height);
	vars->img = mlx_new_image(vars->mlx, vars->width, vars->height);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel,
			&vars->line_length, &vars->endian);
	raytrace_scenario(vars);
	update_image_from_buf(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	mlx_destroy_image(vars->mlx, vars->img);
}

void	mlx_data_init(t_data *vars, const t_args *args)
{
	if (!parse_data_from_file(vars, args->fname))
		clean_exit(vars, "Error parsing data from file", mlx_data_clean, 1);
	vars->buf = ft_calloc(args->width * args->height, sizeof(*vars->buf));
	if (!vars->buf)
		clean_exit(vars, "Error allocating memory to buffer",
			mlx_data_clean, 1);
	vars->width = args->width;
	vars->height = args->height;
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(
			vars->mlx, args->width, args->height, args->title);
}
