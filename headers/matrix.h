/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 15:23:30 by jceia             #+#    #+#             */
/*   Updated: 2021/10/13 12:58:06 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include <stdlib.h>
# include "libft.h"
# include "vec.h"

# ifndef NAN
#  define NAN 0xffffffff
# endif

typedef struct s_matrix
{
	int		ncols;
	int		nrows;
	float	*data;
}	t_matrix;

t_bool		check_matrix_nrows(int nrows, int _nrows);
t_bool		check_matrix_ncols(int ncols, int _ncols);

t_matrix	*matrix_empty(int ncols, int nrows);
void		matrix_clear(t_matrix *m);
t_matrix	*matrix_zeros(int ncols, int nrows);
float		matrix_at(t_matrix *A, int i, int j);
void		matrix_print(t_matrix *m);

t_matrix	*matrix_mul(t_matrix *A, t_matrix *B, t_bool do_free);
t_matrix	*matrix_add(t_matrix *A, t_matrix *B, t_bool do_free);
t_matrix	*matrix_transpose(t_matrix	*m, t_bool do_free);

t_matrix	*matrix3x3_rotation_x(float theta);
t_matrix	*matrix3x3_rotation_y(float theta);
t_matrix	*matrix3x3_rotation_z(float theta);
t_matrix	*matrix3x3_rotation_xyz(const t_vec3d *angles);

t_matrix	*matrix_scaling3d(const t_vec3d *s);
t_vec3d		matrix_mul_vec3d(t_matrix *m, const t_vec3d *p);

#endif
