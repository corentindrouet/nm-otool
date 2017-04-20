/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 09:23:10 by cdrouet           #+#    #+#             */
/*   Updated: 2017/04/20 11:42:48 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static char	search_symbol(t_file_structs *file, struct nlist *sym)
{
	t_section_list	*tmp;
	char			c;

	c = 0;
	if ((SWAP(sym->n_type, file->swap) & N_TYPE) == N_UNDF && !sym->n_value)
		c = 'U';
	else if ((SWAP(sym->n_type, file->swap) & N_TYPE) == N_UNDF && sym->n_value)
		c = 'C';
	else if ((SWAP(sym->n_type, file->swap) & N_TYPE) == N_ABS)
		c = 'A';
	else if ((SWAP(sym->n_type, file->swap) & N_TYPE) == N_INDR)
		c = 'I';
	else if ((SWAP(sym->n_type, file->swap) & N_TYPE) == N_SECT)
	{
		c = 'S';
		tmp = file->sections;
		while (tmp && tmp->index != (int)SWAP(sym->n_sect, file->swap))
			tmp = tmp->next;
		if (!ft_strcmp(tmp->section.sect->sectname, SECT_TEXT))
			c = 'T';
		if (!ft_strcmp(tmp->section.sect->sectname, SECT_BSS))
			c = 'B';
		if (!ft_strcmp(tmp->section.sect->sectname, SECT_DATA))
			c = 'D';
	}
	if (c != 0 && !(SWAP(sym->n_type, file->swap) & N_EXT))
		c += 32;
	return (c);
}

static void	print_output(t_file_structs *file)
{
	uint32_t		i;
	char			*str_table;
	struct nlist	*sym_table;
	t_symtable		*sym_lst;
	t_symtable		*tmp;

	i = 0;
	str_table = (void*)file->file + SWAP(file->sym->stroff, file->swap);
	sym_table = (void*)file->file + SWAP(file->sym->symoff, file->swap);
	sym_lst = NULL;
	while (i < SWAP(file->sym->nsyms, file->swap))
	{
		tmp = create_symtable(&sym_table[i],
			(char*)(str_table + SWAP(sym_table[i].n_un.n_strx, file->swap)));
		add_symtable(&sym_lst, tmp);
		i++;
	}
	sort_symtable(sym_lst);
	tmp = sym_lst;
	while (tmp)
	{
		if (search_symbol(file, tmp->symtable.symtable) && !(tmp->symtable.symtable->n_type & N_STAB))
		{
			if (search_symbol(file, tmp->symtable.symtable) != 'U' &&
					search_symbol(file, tmp->symtable.symtable) != 'u')
				ft_printf("%.8llx ",
						SWAP(tmp->symtable.symtable->n_value, file->swap));
			else
				ft_printf("         ");
			ft_printf("%c %s\n", search_symbol(file, tmp->symtable.symtable),
					tmp->name);
		}
		tmp = tmp->next;
	}
	delete_symtable(sym_lst);
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
	while (i < SWAP(elem->segment.seg->nsects, file->swap))
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
		cmd = (void*)cmd + SWAP(cmd->cmdsize, file->swap);
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
