/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_startswith.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 17:46:07 by jceia             #+#    #+#             */
/*   Updated: 2021/09/01 18:23:47 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_startswith(char *s, char *pref)
{
	int	index;

	index = 0;
	while (s[index] && s[index] == pref[index])
		index++;
	return (pref[index] == 0);
}
