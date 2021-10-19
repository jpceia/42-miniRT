/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:17:16 by jceia             #+#    #+#             */
/*   Updated: 2021/10/13 10:13:52 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "matrix.h"

t_matrix	*matrix_empty(int nrows, int ncols)
{
	t_matrix	*m;

	if (nrows <= 0 || ncols <= 0)
		return (NULL);
	m = (t_matrix *)malloc(sizeof(*m));
	m->nrows = nrows;
	m->ncols = ncols;
	if (!m)
		return (m);
	m->data = (float *)malloc(nrows * ncols * sizeof(*(m->data)));
	if (!(m->data))
	{
		free(m);
		return (NULL);
	}
	return (m);
}

void	matrix_clear(t_matrix *m)
{
	if (m)
	{
		if (m->data)
			free(m->data);
		free(m);
		m = NULL;
	}
}

t_matrix	*matrix_zeros(int nrows, int ncols)
{
	int			idx;
	t_matrix	*m;

	m = matrix_empty(nrows, ncols);
	if (!m)
		return (NULL);
	idx = 0;
	while (idx < nrows * ncols)
		m->data[idx++] = 0;
	return (m);
}

float	matrix_at(t_matrix *A, int i, int j)
{
	if (!A)
	{
		ft_putstr_error("NULL ptr\n");
		return (NAN);
	}
	if (i < 0 || i >= A->nrows)
	{
		ft_putstr_error("Row index outside range\n");
		return (NAN);
	}
	if (j < 0 || j >= A->ncols)
	{
		ft_putstr_error("Column index outside range\n");
		return (NAN);
	}
	return (A->data[i * A->ncols + j]);
}
