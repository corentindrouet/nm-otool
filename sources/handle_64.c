/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 09:41:37 by cdrouet           #+#    #+#             */
/*   Updated: 2017/04/06 15:40:48 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include <stdio.h>

char	search_symbol(t_file_structs *file, struct nlist_64 *sym)
{
	t_section_list	*tmp;

	if ((sym->n_type & N_TYPE) == N_UNDF)
		return ('U');
	if ((sym->n_type & N_TYPE) == N_ABS)
		return ('A');
	if ((sym->n_type & N_TYPE) == N_INDR)
		return ('I');
	if ((sym->n_type & N_TYPE) == N_SECT)
	{
		tmp = file->sections;
		while (tmp && tmp->index != sym->n_sect)
			tmp = tmp->next;
		if (!ft_strcmp(tmp->section.sect_64->sectname, SECT_TEXT))
			return ('T');
	}
	return ('Q');
}

void	print_output(t_file_structs *file)
{
	uint32_t		i;
	char 			*str_table;
	struct nlist_64	*sym_table;
	t_symtable		*sym_lst;
	t_symtable		*tmp;

	i = 0;
	str_table = (void*)file->file + file->sym->stroff;
	sym_table = (void*)file->file + file->sym->symoff;
	sym_lst = NULL;
	while (i < file->sym->nsyms)
	{
		tmp = create_symtable(&sym_table[i],
					(char*)(str_table + sym_table[i].n_un.n_strx));
		add_symtable(&sym_lst, tmp);
		i++;
	}
	sort_symtable(sym_lst);
	tmp = sym_lst;
	while (tmp)
	{
		if (tmp->symtable.symtable_64->n_value)
			printf("%.16llx ", tmp->symtable.symtable_64->n_value);
		else
			printf("                 ");
		printf("%c %s\n", search_symbol(file, tmp->symtable.symtable_64),
				tmp->name);
		tmp = tmp->next;
	}
	delete_symtable(sym_lst);
}

void	add_seg(void *segment, t_file_structs * file)
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

void	handle_64_bits_files(t_file_structs *file)
{
	struct load_command			*cmd;
	uint32_t					i;

	file->headers.header_64 = (struct mach_header_64*)file->file;
	cmd = (void*)file->file + sizeof(struct mach_header_64);
	i = 0;
	while (i < file->headers.header_64->ncmds)
	{
		if (cmd->cmd == LC_SYMTAB)
			file->sym = (void*)cmd;
		cmd = (void*) cmd + cmd->cmdsize;
		i++;
	}
	cmd = (void*)file->file + sizeof(struct mach_header_64);
	i = 0;
	while (i < file->headers.header_64->ncmds)
	{
		if (cmd->cmd == LC_SEGMENT_64)
			add_seg(cmd, file);
		cmd = (void*) cmd + cmd->cmdsize;
		i++;
	}
	print_output(file);
//	print_segments(file->segments);
}
