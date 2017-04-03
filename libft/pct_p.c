/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pct_p.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 09:56:50 by cdrouet           #+#    #+#             */
/*   Updated: 2016/01/26 13:06:25 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pct_p(const char *restrict format, va_list ap)
{
	char	*res;

	res = ft_strnew(1);
	res = ft_strjoin("#", ft_strsub(format, 0, ft_strlen(format) - 1));
	res = ft_strcat(res, "lxp");
	return (pct_x(res, ap));
}
