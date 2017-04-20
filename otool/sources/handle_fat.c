/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 08:36:46 by cdrouet           #+#    #+#             */
/*   Updated: 2017/04/20 13:54:56 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

char		*arch_str(cpu_type_t cputype)
{
	if (cputype == CPU_TYPE_MC680x0)
		return ("mc680x0");
	if (cputype == CPU_TYPE_I386)
		return ("i386");
	if (cputype == CPU_TYPE_X86_64)
		return ("x86_64");
	if (cputype == CPU_TYPE_HPPA)
		return ("hppa");
	if (cputype == CPU_TYPE_ARM)
		return ("arm");
	if (cputype == CPU_TYPE_ARM64)
		return ("arm64");
	if (cputype == CPU_TYPE_MC88000)
		return ("mc88000");
	if (cputype == CPU_TYPE_SPARC)
		return ("sparc");
	if (cputype == CPU_TYPE_I860)
		return ("i860");
	if (cputype == CPU_TYPE_POWERPC ||
			cputype == CPU_TYPE_MC98000)
		return ("ppc");
	if (cputype == CPU_TYPE_POWERPC64)
		return ("ppc64");
	return ("unknown");
}

static int	check_if_host_arch(t_file_structs *file, t_file_structs *fat,
		struct fat_header *file_head, struct fat_arch *file_arch)
{
	uint32_t	i;

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
		init_file_struct(fat, file->file_name);
		fat->file = (void*)file->file + SWAP(file_arch->offset, file->swap);
		fat->file_info->st_size = SWAP(file_arch->size, file->swap);
		nm_file(fat);
		free(fat->file_info);
		return (1);
	}
	return (0);
}

static char	*create_name(t_file_structs *file, struct fat_header *file_head,
		struct fat_arch *file_arch)
{
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(file->file_name) +
			ft_strlen(arch_str(SWAP(file_arch->cputype, file->swap))) + 30));
	ft_bzero(str, (ft_strlen(file->file_name) +
			ft_strlen(arch_str(SWAP(file_arch->cputype, file->swap)) + 24)));
	ft_strcat(str, file->file_name);
	if (SWAP(file_head->nfat_arch, file->swap) != 1)
	{
		ft_strcat(str, " (architecture ");
		ft_strcat(str, arch_str(SWAP(file_arch->cputype, file->swap)));
		ft_strcat(str, ")");
	}
	return (str);
}

void		handle_fat_file(t_file_structs *file)
{
	struct fat_header	*file_head;
	struct fat_arch		*file_arch;
	t_file_structs		fat;
	uint32_t			i;

	file_head = (void*)file->file;
	file_arch = (void*)file_head + sizeof(*file_head);
	if (check_if_host_arch(file, &fat, file_head, file_arch))
		return ;
	i = 0;
	while (i < SWAP(file_head->nfat_arch, file->swap))
	{
		init_file_struct(&fat, create_name(file, file_head, file_arch));
		fat.file = (void*)file->file + SWAP(file_arch->offset, file->swap);
		fat.file_info->st_size = SWAP(file_arch->size, file->swap);
		nm_file(&fat);
		free(fat.file_name);
		free(fat.file_info);
		file_arch += 1;
		i++;
	}
}
