/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deg2_eq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:17:29 by jceia             #+#    #+#             */
/*   Updated: 2021/10/19 10:18:02 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

t_bool	deg2_eq_solutions(const t_deg2_eq_coefs *params, t_float_pair *t)
{
	float			tmp;

	tmp = params->b * params->b - 4 * params->a * params->c;
	if (tmp < 0)
		return (false);
	tmp = sqrtf(tmp);
	t->min = (-params->b - tmp) / (2 * params->a);
	t->max = (-params->b + tmp) / (2 * params->a);
	return (true);
}
