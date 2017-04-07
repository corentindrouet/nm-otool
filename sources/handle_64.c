/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 09:41:37 by cdrouet           #+#    #+#             */
/*   Updated: 2017/04/07 13:12:35 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static char	search_symbol(t_file_structs *file, struct nlist_64 *sym)
{
	t_section_list	*tmp;
	char			c;

	c = 0;
	if ((swap_byte(sym->n_type, sizeof(sym->n_type), file->swap) & N_TYPE) == N_UNDF)
		c = 'U';
	else if ((swap_byte(sym->n_type, sizeof(sym->n_type), file->swap) & N_TYPE) == N_ABS)
		c = 'A';
	else if ((swap_byte(sym->n_type, sizeof(sym->n_type), file->swap) & N_TYPE) == N_INDR)
		c = 'I';
	else if ((swap_byte(sym->n_type, sizeof(sym->n_type), file->swap) & N_TYPE) == N_SECT)
	{
		tmp = file->sections;
		while (tmp && tmp->index != (int)swap_byte(sym->n_sect, sizeof(sym->n_sect, file->swap), file->swap))
			tmp = tmp->next;
		if (!ft_strcmp(tmp->section.sect_64->sectname, SECT_TEXT))
			c = 'T';
	}
	if (c != 0 && !(swap_byte(sym->n_type, sizeof(sym->n_type), file->swap) & N_EXT))
		c += 32;
	return (c);
}

static void	print_output(t_file_structs *file)
{
	uint32_t		i;
	char 			*str_table;
	struct nlist_64	*sym_table;
	t_symtable		*sym_lst;
	t_symtable		*tmp;

	i = 0;
	str_table = (void*)file->file + swap_byte(file->sym->stroff, sizeof(file->sym->stroff), file->swap);
	sym_table = (void*)file->file + swap_byte(file->sym->symoff, sizeof(file->sym->symoff), file->swap);
	sym_lst = NULL;
	while (i < swap_byte(file->sym->nsyms, sizeof(file->sym->nsyms), file->swap))
	{
		tmp = create_symtable(&sym_table[i],
					(char*)(str_table + swap_byte(sym_table[i].n_un.n_strx, sizeof(sym_table[i].n_un.n_strx), file->swap)));
		add_symtable(&sym_lst, tmp);
		i++;
	}
	sort_symtable(sym_lst);
	tmp = sym_lst;
	while (tmp)
	{
		if (search_symbol(file, tmp->symtable.symtable_64))
		{
			if (swap_byte(tmp->symtable.symtable_64->n_value, sizeof(tmp->symtable.symtable_64->n_value), file->swap))
				ft_printf("%.16llx ", swap_byte(tmp->symtable.symtable_64->n_value, sizeof(tmp->symtable.symtable_64->n_value), file->swap));
			else
				ft_printf("                 ");
			ft_printf("%c %s\n", search_symbol(file, tmp->symtable.symtable_64),
					tmp->name);
		}
		tmp = tmp->next;
	}
	delete_symtable(sym_lst);
	delete_section_lst(file->sections);
	delete_segment_lst(file->segments);
}

static void	add_seg(void *segment, t_file_structs * file)
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
	while (i < swap_byte(file->headers.header_64->ncmds, sizeof(file->headers.header_64->ncmds), file->swap))
	{
		if (swap_byte(cmd->cmd, sizeof(cmd->cmd), file->swap) == LC_SYMTAB)
			file->sym = (void*)cmd;
		cmd = (void*) cmd + swap_byte(cmd->cmdsize, sizeof(cmd->cmdsize), file->swap);
		i++;
	}
	cmd = (void*)file->file + sizeof(struct mach_header_64);
	i = 0;
	while (i < swap_byte(file->headers.header_64->ncmds, sizeof(file->headers.header_64->ncmds), file->swap))
	{
		if (swap_byte(cmd->cmd, sizeof(cmd->cmd), file->swap) == LC_SEGMENT_64)
			add_seg(cmd, file);
		cmd = (void*) cmd + swap_byte(cmd->cmdsize, sizeof(cmd->cmdsize), file->swap);
		i++;
	}
	print_output(file);
}
