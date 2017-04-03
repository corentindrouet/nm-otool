/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 09:19:24 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/31 09:43:50 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	nm_file(char *ptr)
{
	unsigned int	magic;

	magic = *(unsigned int*)ptr;
	if (magic == MH_MAGIC)
		ft_putendl("That a 32 bits file");
	else if (magic == MH_MAGIC_64)
		handle_64_bits_files(ptr);
	else
		error_exit("File type unknown", NULL, EXIT_FAILURE);
}
