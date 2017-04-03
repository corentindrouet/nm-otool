/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 09:45:45 by cdrouet           #+#    #+#             */
/*   Updated: 2016/02/01 08:38:47 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	**init_color(void)
{
	char	**ptr;
	int		i;

	ptr = (char**)malloc(sizeof(char*) * 9);
	i = -1;
	while (++i < 9)
		ptr[i] = ft_strnew(8);
	ptr[0] = ft_strcpy(ptr[0], "noir");
	ptr[1] = ft_strcpy(ptr[1], "rouge");
	ptr[2] = ft_strcpy(ptr[2], "vert");
	ptr[3] = ft_strcpy(ptr[3], "jaune");
	ptr[4] = ft_strcpy(ptr[4], "bleu");
	ptr[5] = ft_strcpy(ptr[5], "rose");
	ptr[6] = ft_strcpy(ptr[6], "cyan");
	ptr[7] = ft_strcpy(ptr[7], "gris");
	ptr[8] = ft_strcpy(ptr[8], "eoc");
	return (ptr);
}

int			ft_color(char *color)
{
	char	**ptr;
	int		i;
	char	*prcolor;

	ptr = init_color();
	i = -1;
	while (++i < 9)
		if (!ft_strcmp(color, ptr[i]))
			break ;
	if (i == 9)
		return (0);
	prcolor = ft_strnew(8);
	prcolor = ft_strcpy(prcolor, "\033[");
	if (i < 8)
		prcolor = ft_strcat(prcolor, ft_itoa(i + 30));
	else
		prcolor = ft_strcat(prcolor, "0");
	prcolor = ft_strcat(prcolor, "m");
	ft_putstr(prcolor);
	return (ft_strlen(prcolor));
}

static void	print_else(char **ptr, int *i)
{
	write(1, &(*ptr)[(*i)], 1);
	(*ptr) = &(*ptr)[(*i) + 1];
	(*i) = -1;
}

void		print_str_color(char *str)
{
	int		i;
	char	*ptr;
	char	*secur;

	ptr = ft_strjoin("", str);
	secur = ptr;
	i = -1;
	while (ptr[++i])
		if (ptr[i] == '{')
		{
			write(1, ptr, i);
			if (ft_strchr(&str[i], '}') != NULL &&
				ft_color(ft_strsub(&ptr[i + 1], 0,
					cont_carac(&ptr[i + 1], '}'))) != 0)
			{
				ptr = ft_strchr(ptr, '}') + 1;
				i = -1;
			}
			else
				print_else(&ptr, &i);
		}
	write(1, ptr, i);
	free(secur);
}
