/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 11:38:02 by cdrouet           #+#    #+#             */
/*   Updated: 2017/04/14 14:09:17 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

uint64_t	swap_byte(uint64_t a, int size, int need_swap)
{
	uint64_t	ret;
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
	return (ret);
}