/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 11:38:02 by cdrouet           #+#    #+#             */
/*   Updated: 2017/04/20 10:06:46 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

uint64_t	swap_byte(uint64_t a, int size, int need_swap)
{
	char	*ok;
	char	tmp;
	int		i;

	if (!need_swap)
		return (a);
	i = 0;
	ok = (char*)&a;
	while (i < (size / 2))
	{
		tmp = ok[i];
		ok[i] = ok[size - 1 - i];
		ok[size - 1 - i] = tmp;
		i++;
	}
	return (a);
/*	uint64_t	ret;
	int			i;
	int			dec;

	if (!need_swap)
		return (a);
	ret = 0;
	i = 0;
	dec = 0;
	while (((size - 1) - i) > 0)
	{
		ret |= ((a >> (((size - 1) - i) * 8)) & ((uint64_t)0xff << (dec * 8)));
		i += 2;
		dec++;
	}
	i = 0;
	while (i < size)
	{
		ret |= ((a << ((i + 1) * 8)) & ((uint64_t)0xff << (dec * 8)));
		i += 2;
		dec++;
	}
	return (ret);*/
}
