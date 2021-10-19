/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 02:53:52 by jceia             #+#    #+#             */
/*   Updated: 2021/10/14 18:32:16 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

float	fclipf(float x, float min, float max)
{
	return (fminf(fmaxf(x, min), max));
}

int	create_trgb(t_rgb v)
{
	return (
		(0) << 24
		| ((int)(255 * fclipf(v.x, 0, 1))) << 16
		| ((int)(255 * fclipf(v.y, 0, 1))) << 8
		| ((int)(255 * fclipf(v.z, 0, 1)))
	);
}

int	get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

int	get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

int	get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}
