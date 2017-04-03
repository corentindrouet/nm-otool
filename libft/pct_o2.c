/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pct_o2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 09:42:15 by cdrouet           #+#    #+#             */
/*   Updated: 2016/02/04 09:15:55 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pct_jo(va_list ap, const char *restrict format, int base, int maj)
{
	intmax_t	ptr;
	char		*res;
	int			nb1;
	int			nb2;

	nb1 = 0;
	nb2 = 0;
	while (format[++nb2])
		if (format[nb2] == '*')
			nb1++;
	init(&nb1, &nb2, ap);
	ptr = (intmax_t)va_arg(ap, intmax_t);
	res = ft_ulltoa_base((long long)ptr, base);
	res = precis_d(&res, format, nb2);
	res = width_d(&res, format, nb1, nb2);
	if (base > 10 && maj == 1)
		ft_strtoupper(res);
	if (ft_strchr(format, '#') != NULL)
		res = ft_diese(format, &res, base, maj);
	ft_putstr(res);
	return (ft_strlen(res));
}

int		pct_zo(va_list ap, const char *restrict format, int base, int maj)
{
	size_t	ptr;
	char	*res;
	int		nb1;
	int		nb2;

	nb1 = 0;
	nb2 = 0;
	while (format[++nb2])
		if (format[nb2] == '*')
			nb1++;
	init(&nb1, &nb2, ap);
	ptr = (size_t)va_arg(ap, size_t);
	res = ft_ulltoa_base((long long)ptr, base);
	res = precis_d(&res, format, nb2);
	res = width_d(&res, format, nb1, nb2);
	if (base > 10 && maj == 1)
		ft_strtoupper(res);
	if (ft_strchr(format, '#') != NULL)
		res = ft_diese(format, &res, base, maj);
	ft_putstr(res);
	return (ft_strlen(res));
}

int		pct_oo(va_list ap, const char *restrict format, int base, int maj)
{
	unsigned int	ptr;
	char			*res;
	int				nb1;
	int				nb2;

	nb1 = 0;
	nb2 = 0;
	while (format[++nb2])
		if (format[nb2] == '*')
			nb1++;
	init(&nb1, &nb2, ap);
	ptr = (unsigned int)va_arg(ap, unsigned int);
	res = ft_uitoa_base((unsigned int)ptr, base);
	res = precis_d(&res, format, nb2);
	res = width_d(&res, format, nb1, nb2);
	if (base > 10 && maj == 1)
		ft_strtoupper(res);
	if (ft_strchr(format, '#') != NULL)
		res = ft_diese(format, &res, base, maj);
	ft_putstr(res);
	return (ft_strlen(res));
}

void	ft_strtoupper(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = ft_toupper(str[i]);
}
