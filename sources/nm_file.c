/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 09:19:24 by cdrouet           #+#    #+#             */
/*   Updated: 2017/04/06 12:46:17 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	nm_file(t_file_structs *file)
{
	unsigned int	magic;

	magic = *(unsigned int*)(file->file);
	if (magic == MH_MAGIC)
		ft_putendl("That a 32 bits file");
	else if (magic == MH_MAGIC_64)
		handle_64_bits_files(file);
	else
		error_exit("File type unknown", NULL, EXIT_FAILURE);
}
