/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_f4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 13:50:27 by cdrouet           #+#    #+#             */
/*   Updated: 2016/02/04 14:28:12 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			init_diese_i(char **ptr)
{
	int	i;

	i = 0;
	while ((*ptr)[i] == ' ')
		i++;
	if (!(*ptr)[i])
		i = 0;
	return (i);
}

char		*all_flag_spe(long long i,
		const char *restrict format, int nb1, int nb2)
{
	char	*r;

	if (i >= 0)
		r = ft_lltoa(i);
	else
		r = ft_strsub(ft_lltoa(i), 1, ft_strlen(ft_lltoa(i)) - 1);
	r = precis_d(&r, format, nb2);
	r = plus_d(&r, format, i);
	r = width_d(&r, format, nb1, nb2);
	return (r);
}
