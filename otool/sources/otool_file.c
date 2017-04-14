/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 09:19:24 by cdrouet           #+#    #+#             */
/*   Updated: 2017/04/14 14:09:08 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int		need_swap(unsigned int magic)
{
	return (magic == MH_CIGAM || magic == MH_CIGAM_64);
}

void	nm_file(t_file_structs *file)
{
	unsigned int	magic;

	magic = *(unsigned int*)(file->file);
	file->swap = need_swap(magic);
	if (magic == MH_MAGIC || magic == MH_CIGAM)
		handle_32_bits_files(file);
	else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		handle_64_bits_files(file);
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		handle_fat_file(file);
	else if (!ft_memcmp(file->file, "!<arch>\n", 8))
		handle_archives(file);
}
