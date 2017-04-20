/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 09:41:37 by cdrouet           #+#    #+#             */
/*   Updated: 2017/04/20 13:36:38 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	print_content(t_section_list *tmp, t_file_structs *file)
{
	char			*ptr;
	uint64_t		i;
	uint64_t		addr;

	ptr = (void*)file->file + tmp->section.sect_64->offset;
	addr = tmp->section.sect_64->addr;
	ft_printf("%s:\nContents of (__TEXT,__text) section", file->file_name);
	i = 0;
	while (i < tmp->section.sect_64->size)
	{
		if ((i % 16) == 0)
			ft_printf("\n%.16llx\t", addr);
		ft_printf("%.2hhx", (char)ptr[i]);
		if (file->swap && ((i + 1) % 8) == 0)
			ft_printf(" ");
		else if (!file->swap)
			ft_printf(" ");
		i++;
		addr++;
	}
	ft_printf("\n");
}

static void	print_output(t_file_structs *file)
{
	t_section_list	*tmp;

	tmp = file->sections;
	while (tmp)
	{
		if (!ft_strcmp(tmp->section.sect_64->segname, SEG_TEXT) &&
				!ft_strcmp(tmp->section.sect_64->sectname, SECT_TEXT))
			break ;
		tmp = tmp->next;
	}
	print_content(tmp, file);
	delete_section_lst(file->sections);
	delete_segment_lst(file->segments);
}

static void	add_seg(void *segment, t_file_structs *file)
{
	struct section_64			*tmp_sect;
	t_section_list				*tmp_sect_add;
	t_segment_list				*elem;
	uint32_t					i;

	elem = create_segment(segment);
	add_segment(&(file->segments), elem);
	i = 0;
	tmp_sect = (void*)elem->segment.seg_64 + sizeof(struct segment_command_64);
	while (i < elem->segment.seg_64->nsects)
	{
		tmp_sect_add = create_section(tmp_sect);
		if (i == 0)
			elem->first_section = tmp_sect_add;
		add_section(&(file->sections), tmp_sect_add);
		i++;
		tmp_sect = (void*)tmp_sect + sizeof(struct section_64);
	}
}

void		handle_64_bits_files(t_file_structs *file)
{
	struct load_command			*cmd;
	uint32_t					i;

	file->headers.header_64 = (struct mach_header_64*)file->file;
	cmd = (void*)file->file + sizeof(struct mach_header_64);
	i = 0;
	while (i < SWAP(file->headers.header_64->ncmds, file->swap))
	{
		if (SWAP(cmd->cmd, file->swap) == LC_SYMTAB)
			file->sym = (void*)cmd;
		cmd = (void*)cmd + SWAP(cmd->cmdsize, file->swap);
		i++;
	}
	cmd = (void*)file->file + sizeof(struct mach_header_64);
	i = 0;
	while (i < SWAP(file->headers.header_64->ncmds, file->swap))
	{
		if (SWAP(cmd->cmd, file->swap) == LC_SEGMENT_64)
			add_seg(cmd, file);
		cmd = (void*)cmd + SWAP(cmd->cmdsize, file->swap);
		i++;
	}
	print_output(file);
}
