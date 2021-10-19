/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 17:30:19 by jceia             #+#    #+#             */
/*   Updated: 2021/10/13 10:18:20 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "libft.h"

t_bool	check_matrix_nrows(int nrows, int _nrows)
{
	if (nrows != _nrows)
	{
		ft_putstr_error("Row number mismatch\n");
		return (false);
	}
	return (true);
}

t_bool	check_matrix_ncols(int ncols, int _ncols)
{
	if (ncols != _ncols)
	{
		ft_putstr_error("Column number mismatch\n");
		return (false);
	}
	return (true);
}
