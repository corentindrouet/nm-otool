/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 09:41:37 by cdrouet           #+#    #+#             */
/*   Updated: 2017/04/03 15:43:08 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include <stdio.h>

void	print_output(char *ptr, struct symtab_command *sym)
{
	uint32_t		i;
	char 			*str_table;
	struct nlist_64	*sym_table;

	i = 0;
	str_table = (void*)ptr + sym->stroff;
	sym_table = (void*)ptr + sym->symoff;
	while (i < sym->nsyms)
	{
		printf("%s %d\n", str_table + sym_table[i].n_un.n_strx,
				(uint8_t)(str_table + sym_table[i].n_sect));
		i++;
	}
}

void	print_seg_name(void *segment, char *ptr)
{
	struct segment_command_64	*seg;
	(void)ptr;
	struct section_64			*sec;
	uint32_t					i;

	seg = segment;
	printf("  cmd %d\n", seg->cmd);
	printf("  cmdsize %d\n", seg->cmdsize);
	printf("  segname %s\n", seg->segname);
	printf("  nsects %d\n", seg->nsects);
	i = 0;
	sec = (void*)seg + sizeof(struct segment_command_64);
	while (i < seg->nsects)
	{
		printf("    addr %llx\n", sec->addr);
		printf("    offset %d\n", sec->offset);
//		printf("    align %d\n", sec->align);
//		write(1, (ptr + sec->offset), sec->size);
//		write(1, "\n", 1);
		i++;
		sec = (void*)sec + sizeof(struct section_64);
	}
	printf("  flags %d\n", seg->flags);
	printf("\n");
//	printf("  %s %llx %d\n", seg->segname, seg->vmaddr, seg->nsects);
}

void	handle_64_bits_files(char *ptr)
{
	struct mach_header_64		*header;
	struct load_command			*cmd;
	struct symtab_command		*sym;
	uint32_t					i;

	header = (struct mach_header_64*)ptr;
	cmd = (void*)ptr + sizeof(*header);
	i = 0;
	printf("%d\n", header->ncmds);
	while (i < header->ncmds)
	{
		if (cmd->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command*)cmd;
			print_output(ptr, sym);
		}
		else if (cmd->cmd == LC_SEGMENT_64)
			print_seg_name(cmd, ptr);
		else
			printf("%x\n", cmd->cmd);
		cmd = (void*) cmd + cmd->cmdsize;
		i++;
	}
}
