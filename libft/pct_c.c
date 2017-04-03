/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pct_c.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 10:23:01 by cdrouet           #+#    #+#             */
/*   Updated: 2016/02/04 09:37:05 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putmem(char *str, int i)
{
	write(1, str, i);
}

static int	pct_cc2(char *str, char ptr, int nb1)
{
	int		i;

	i = 0;
	if (ptr == 0)
	{
		i = ft_strlen(&str[1]) + 1;
		str[0] = '\0';
		if (nb1 < 0)
			ft_putmem(str, i);
		else
			ft_putmem(&str[1], i);
		str[0] = ' ';
	}
	else
		ft_putstr(str);
	if (ft_strlen(str) == 0)
		return (1);
	return (ft_strlen(str));
}

static int	pct_cc(const char *restrict format, va_list ap)
{
	char	ptr;
	char	*str;
	int		i;
	int		nb1;
	int		nb2;

	nb1 = 0;
	nb2 = -1;
	while (format[++nb2])
		if (format[nb2] == '*')
			nb1++;
	init(&nb1, &nb2, ap);
	ptr = (char)va_arg(ap, int);
	i = 0;
	while (format[i] && !ft_isdigit(format[i]) && format[i] != '*')
		i++;
	str = ft_strnew(2);
	str[0] = ptr;
	if (format[i - 1] != '.')
		str = decal_c(&str, format, nb1);
	return (pct_cc2(str, ptr, nb1));
}

int			pct_lc(const char *restrict format, va_list ap)
{
	wchar_t	res;
	wchar_t	*pr;
	int		nb1;
	int		nb2;

	nb1 = 0;
	nb2 = -1;
	while (format[++nb2])
		if (format[nb2] == '*')
			nb1++;
	init(&nb1, &nb2, ap);
	res = (wchar_t)va_arg(ap, wchar_t);
	pr = (wchar_t*)malloc(sizeof(wchar_t) * 2);
	pr[1] = 0;
	pr[0] = res;
	pr = decal_wstr(&pr, format, (int)nb1);
	if (res == 0 && ft_wstrlen(pr) == 0)
		return (ft_putwmem(pr, ft_wstrlen(pr) + 1));
	else if (res == 0)
		return (ft_putwmem(&pr[1], ft_wstrlen(pr)));
	return (ft_putwstr_t(pr));
}

int			pct_c(const char *restrict format, va_list ap)
{
	if (ft_strchr(format, 'l') == NULL)
		return (pct_cc(format, ap));
	else
		return (pct_lc(format, ap));
	return (0);
}
