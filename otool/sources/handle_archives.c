/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_archives.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 12:40:30 by cdrouet           #+#    #+#             */
/*   Updated: 2017/04/14 15:02:21 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	handle_archives(t_file_structs *file)
{
	t_arch_header	*arch_header;
	uint32_t		*info;
	int				name_length;
	t_file_structs	archived;
	int				i;
	char			*name;

	arch_header = (void*)file->file + 8;
	name_length = ft_atoi(&(arch_header->name[3]));
	info = (void*)arch_header + sizeof(t_arch_header) + name_length;
	arch_header = (void*)(info + 1) + *info +
		4 + *(uint32_t*)((void*)(info + 1) + *info);
	i = 0;
	ft_printf("Archive : %s\n", file->file_name);
	while (((void*)arch_header - (void*)file->file) < file->file_info->st_size)
	{
		init_file_struct(&archived, (char*)arch_header + sizeof(*arch_header));
		archived.file = (void*)arch_header + sizeof(*arch_header) +
			ft_atoi(&(arch_header->name[3]));
		name = malloc(ft_strlen(file->file_name) + ft_strlen(archived.file_name) + 3);
		name[0] = '\0';
		ft_strcat(name, file->file_name);
		ft_strcat(name, "(");
		ft_strcat(name, archived.file_name);
		ft_strcat(name, ")");
		archived.file_name = name;
		nm_file(&archived);
		free(archived.file_info);
		free(archived.file_name);
		arch_header = (void*)arch_header + sizeof(*arch_header) +
			ft_atoi(arch_header->size);
	}
}
