/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 09:23:10 by cdrouet           #+#    #+#             */
/*   Updated: 2017/04/14 14:35:47 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void	print_output(t_file_structs *file)
{
	t_section_list	*tmp;
	char			*ptr;
	uint32_t		i;
	uint32_t		addr;

	tmp = file->sections;
	while (tmp)
	{
		if (!ft_strcmp(tmp->section.sect->segname, SEG_TEXT) &&
				!ft_strcmp(tmp->section.sect->sectname, SECT_TEXT))
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	ptr = (void*)file->file + tmp->section.sect->offset;
	addr = tmp->section.sect->addr;
	ft_printf("%s:\nContents of (__TEXT,__text) section", file->file_name);
	i = 0;
	while (i < tmp->section.sect->size)
	{
		if ((i % 16) == 0)
			ft_printf("\n%.8llx\t", addr);
		ft_printf("%.2hhx ", (char)ptr[i]);
		i++;
		addr++;
	}
	ft_printf("\n");
	delete_section_lst(file->sections);
	delete_segment_lst(file->segments);
}

static void	add_seg(void *segment, t_file_structs *file)
{
	struct section				*tmp_sect;
	t_section_list				*tmp_sect_add;
	t_segment_list				*elem;
	uint32_t					i;

	elem = create_segment(segment);
	add_segment(&(file->segments), elem);
	i = 0;
	tmp_sect = (void*)elem->segment.seg + sizeof(struct segment_command);
	while (i < elem->segment.seg->nsects)
	{
		tmp_sect_add = create_section(tmp_sect);
		if (i == 0)
			elem->first_section = tmp_sect_add;
		add_section(&(file->sections), tmp_sect_add);
		i++;
		tmp_sect = (void*)tmp_sect + sizeof(struct section);
	}
}

void		handle_32_bits_files(t_file_structs *file)
{
	struct load_command			*cmd;
	uint32_t					i;

	file->headers.header = (struct mach_header*)file->file;
	cmd = (void*)file->file + sizeof(struct mach_header);
	i = 0;
	while (i < SWAP(file->headers.header->ncmds, file->swap))
	{
		if (SWAP(cmd->cmd, file->swap) == LC_SYMTAB)
			file->sym = (void*)cmd;
		cmd = (void*)cmd + cmd->cmdsize;
		i++;
	}
	if (!file->sym)
		return ;
	cmd = (void*)file->file + sizeof(struct mach_header);
	i = 0;
	while (i < SWAP(file->headers.header->ncmds, file->swap))
	{
		if (SWAP(cmd->cmd, file->swap) == LC_SEGMENT)
			add_seg(cmd, file);
		cmd = (void*)cmd + SWAP(cmd->cmdsize, file->swap);
		i++;
	}
	print_output(file);
}
