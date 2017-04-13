/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 08:36:46 by cdrouet           #+#    #+#             */
/*   Updated: 2017/04/13 13:06:42 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	handle_fat_file(t_file_structs *file)
{
	struct fat_header	*file_head;
	struct fat_arch		*file_arch;
	t_file_structs		fat;
	uint32_t			i;

	file_head = (void*)file->file;
	if (file_head->magic == FAT_CIGAM)
		file->swap = 1;
	file_arch = (void*)file_head + sizeof(*file_head);
	i = 0;
	while (i < SWAP(file_head->nfat_arch, file->swap))
	{
		if (host_arch() == 64 &&
				SWAP(file_arch->cputype, file->swap) & CPU_ARCH_ABI64)
			break ;
		file_arch += 1;
		i++;
	}
	if (i < SWAP(file_head->nfat_arch, file->swap))
	{
		init_file_struct(&fat, "obj");
		fat.file = (void*)file->file + SWAP(file_arch->offset, file->swap);
		nm_file(&fat);
		free(fat.file_info);
		return ;
	}
	i = 0;
	while (i < SWAP(file_head->nfat_arch, file->swap))
	{
		init_file_struct(&fat, "obj");
		fat.file = (void*)file->file + SWAP(file_arch->offset, file->swap);
		nm_file(&fat);
		free(fat.file_info);
		file_arch += 1;
		i++;
	}
}
